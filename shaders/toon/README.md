
# Toon Shader

A simple implementation of Toon Shading (Cel Shading) with outlines.

The outlines are rendered by using a basic color shader and rendering the back faces in thicker lines. Then, the front faces and rendered after.

- Settings
```C++
GLRenderSystem gl_render_system = GLRenderSystem();

gl_render_system.Enable(GL_DEPTH_TEST);
gl_render_system.Enable(GL_CULL_FACE);
gl_render_system.SetPolygonMode(GL_BACK, GL_LINE);
gl_render_system.SetPolygonMode(GL_FRONT, GL_FILL);
```
- Render Loop
```C++
gl_render_system.BindProgram("basic"); //normal color shader.
gl_render_system.SetLineWidth(6.0f);
gl_render_system.SetCullFace(GL_FRONT);
gl_render_system.Draw(GL_TRIANGLES, 0, test_vertices.size());

gl_render_system.BindProgram("toon"); //cel shader.
gl_render_system.SetCullFace(GL_BACK);
gl_render_system.Draw(GL_TRIANGLES, 0, test_vertices.size());
```


Parameters for the Toon Fragment Shader:
```C++
uniform vec3 light_direction;
```


## Gallery

![toon sphere](https://github.com/xz1a/GLSandbox/blob/main/gallery/toon_sphere.JPG)
![toon cube](https://github.com/xz1a/GLSandbox/blob/main/gallery/toon_cube.JPG)
![toon torus](https://github.com/xz1a/GLSandbox/blob/main/gallery/toon_torus.JPG)