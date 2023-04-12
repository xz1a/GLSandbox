#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "GLRenderSystem.h"

const float vertices[] = {
    -1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

int main(int argc, char* argv[]) {
	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1280, 720, "GL Sandbox", NULL, NULL);
	glfwMakeContextCurrent(window);
	gl3wInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	glm::vec3 projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	glm::vec3 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0f, 1.0f, 0.0f));

	GLBufferLayout layout = GLBufferLayout({
		GLBufferLayoutElement {3, GL_FLOAT, false, NULL},
	});
	GLRenderSystem gl_render_system = GLRenderSystem();
	std::shared_ptr<GLBuffer> vbo = gl_render_system.CreateBuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
	std::shared_ptr<GLVertexArray> vao = gl_render_system.CreateVertexArray(layout1, vbo);

	std::shared_ptr<GLProgram> program = gl_render_system.CreateProgram(
		"basic",
		{
			{"./shaders/basic.vertex", GL_VERTEX_SHADER},
			{"./shaders/basic.fragment", GL_FRAGMENT_SHADER}
		}
    );

    program.get()->SetUniformMat4("model", glm::mat4(1.0), false);
    program.get()->SetUniformMat4("view", view, false);
    program.get()->SetUniformMat4("projection", projection, false);
    
	while (!glfwWindowShouldClose(window)) {
		gl_render_system.Clear();
		gl_render_system.BindProgram("basic");
		gl_render_system.BindVertexArray(vao);
		gl_render_system.Draw(GL_TRIANGLES, 0, test_vertices.size());
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}