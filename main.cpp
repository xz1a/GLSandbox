#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include "GLRenderSystem.h"
#include "SimpleObjLoader.h"
#include <glm/gtx/string_cast.hpp>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stbi.h"

typedef struct Camera {
	glm::vec3 position;
	glm::mat4 projection;
	glm::mat4 view;
	glm::vec3 view_target;
} Camera;

int main(int argc, char* argv[]) {
	if (!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "GL Sandbox", NULL, NULL);
	glfwMakeContextCurrent(window);
	gl3wInit();

	GLBufferLayout layout = GLBufferLayout({
		GLBufferLayoutElement {3, GL_FLOAT, false, NULL},
		GLBufferLayoutElement {3, GL_FLOAT, false, NULL},
		GLBufferLayoutElement {2, GL_FLOAT, false, NULL},
		GLBufferLayoutElement {4, GL_FLOAT, false, NULL},
	});

	GLRenderSystem gl_render_system = GLRenderSystem(1280, 720);

	std::vector<Vertex> test_vertices;
	SimpleObjLoader::LoadObj("./meshes/cube.obj", test_vertices);
	srand(time(NULL));
	float x = ((float)rand() / (RAND_MAX));
	float y = ((float)rand() / (RAND_MAX));
	float z = ((float)rand() / (RAND_MAX));
	for (int i = 0; i < test_vertices.size(); ++i) {
		test_vertices[i].color = glm::vec4(x, y, z, 1.0f);
	}

	std::shared_ptr<GLBuffer> vbo = gl_render_system.CreateBuffer(GL_ARRAY_BUFFER, test_vertices.data(), test_vertices.size() * sizeof(Vertex));
	std::shared_ptr<GLVertexArray> vao = gl_render_system.CreateVertexArray({ {layout, vbo} });

	Camera camera;
	camera.position = glm::vec3(0.0f, 0.0f, 15.0f);
	camera.projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	camera.view_target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera.view = glm::lookAt(camera.position, camera.view_target, glm::vec3(0.0f, 1.0f, 0.0f));

	std::shared_ptr<GLProgram> shader = gl_render_system.CreateProgram("gbuffer", {
		{"./shaders/deferred_shading/gbuffer.vertex", GL_VERTEX_SHADER },
		{"./shaders/deferred_shading/gbuffer.fragment", GL_FRAGMENT_SHADER }
	});

	glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader->SetUniformMat4("model_view_matrix", camera.view * model, false);
	shader->SetUniformMat4("projection_matrix", camera.projection, false);
	shader->SetUniformMat3("normal_matrix", glm::mat3(glm::transpose(glm::inverse(camera.view * model))), false);

	std::shared_ptr<GLFrameBuffer> gbuffer = gl_render_system.CreateFrameBuffer(1280, 720, {
		{1, GL_RGB16F, GL_COLOR_ATTACHMENT0},
		{1, GL_RGB16F, GL_COLOR_ATTACHMENT1},
		{1, GL_DEPTH_COMPONENT32F, GL_DEPTH_ATTACHMENT}
	});

	gl_render_system.Enable(GL_MULTISAMPLE);
	gl_render_system.Enable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gl_render_system.BindFrameBuffer(gbuffer);
		gl_render_system.BindProgram("gbuffer");
		gl_render_system.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gl_render_system.BindVertexArray(vao);
		gl_render_system.Draw(GL_TRIANGLES, 0, test_vertices.size());
		gl_render_system.UnBindFrameBuffer();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}