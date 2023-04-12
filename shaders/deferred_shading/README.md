
# Deferred Shading

Implementation of Deferred Shading.

FrameBuffer Construction:
```
std::shared_ptr<GLFrameBuffer> gbuffer = gl_render_system.CreateFrameBuffer(1280, 720, {
    {1, GL_RGB16F, GL_COLOR_ATTACHMENT0}, //Position Attachement
    {1, GL_RGB16F, GL_COLOR_ATTACHMENT1}, //Normal Attachment
    {1, GL_DEPTH_COMPONENT32F, GL_DEPTH_ATTACHMENT}
});
```

G-Buffer Vertex Shader:
```
#version 450 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_uv;
layout (location = 3) in vec4 vertex_color;

out vec4 viewspace_position;
out vec3 normal;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix;

void main()
{
    viewspace_position = model_view_matrix * vec4(vertex_position, 1.0);
    normal = normalize(normal_matrix * vertex_normal);
    gl_Position = projection_matrix * viewspace_position;
}
```
G-Buffer Fragment Shader:
```
#version 450 core
layout (location = 0) out vec3 gbuffer_position;
layout (location = 1) out vec3 gbuffer_normal;

in vec4 viewspace_position;
in vec3 normal;

void main()
{    
    gbuffer_position = viewspace_position.xyz;
    gbuffer_normal = normalize(normal);
}
```

The Rendering Loop:
```
//G-Buffer Pass
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
gl_render_system.BindFrameBuffer(gbuffer);
gl_render_system.BindProgram("gbuffer");
gl_render_system.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
gl_render_system.BindVertexArray(vao);
gl_render_system.Draw(GL_TRIANGLES, 0, test_vertices.size());
gl_render_system.UnBindFrameBuffer();

//Lighting Pass
bind lighting shader
gl_render_system.BindFrameBufferTextures(gbuffer);
Render Quad
```

G-Buffer Example:
![](https://github.com/xz1a/GLSandbox/blob/main/gallery/gbuffer.JPG)