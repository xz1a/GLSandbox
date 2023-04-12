# Enviroment Mapping Shader

A simple implementation of Enviroment Mapping with a Skybox.

- Shader Parameters
```
uniform samplerCube skybox_texture;
uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix;
```
- Render Loop
```
render_system.Enable(GL_DEPTH_TEST);
render_system.Enable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
render_system.Disable(GL_CULL_FACE);

while(1) {
    //Render Objects
    //Render Skybox
}
```

![skybox1](https://github.com/xz1a/GLSandbox/blob/main/gallery/env_map_1.jpg)
![skybox2](https://github.com/xz1a/GLSandbox/blob/main/gallery/env_map_2.jpg)