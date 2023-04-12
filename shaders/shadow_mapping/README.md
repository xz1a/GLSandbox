
# Shadow Mapping

Shadow Mapping Using OpenGL



## Directional Light

A 1024x1024 Shadow Map Texture is generated from the point of view of the light.

The Texture:
![](https://github.com/xz1a/GLSandbox/blob/main/gallery/sample_shadow_map.JPG)

The Rendering Loop:
```
gl_render_system.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//Shadow Pass
gl_render_system.BindFrameBuffer(shadow_buffer);
gl_render_system.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
gl_render_system.BindProgram("shadow");
gl_render_system.SetClearColor(1.0, 1.0, 1.0, 1.0);

gl_render_system.Enable(GL_POLYGON_OFFSET_FILL);
gl_render_system.SetPolygonOffest(2.0f, 4.0f);
for (int i = 0; i < counts; ++i) {
    shader->SetUniformMat4("model_matrix", models[i], false);
    gl_render_system.Draw(GL_TRIANGLES, 0, test_vertices.size());
}
gl_render_system.Disable(GL_POLYGON_OFFSET_FILL);

//Lighting Pass
gl_render_system.UnBindFrameBuffer();
gl_render_system.SetClearColor(0.0, 0.6, 0.8, 1.0);
gl_render_system.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
gl_render_system.BindProgram("lighting_shader");
gl_render_system.BindFrameBufferTextures(shadow_buffer);
for (int i = 0; i < counts; ++i) {
    lighting_shader->SetUniformMat4("shadow_matrix", shadow_matrix * models[i], false);
    lighting_shader->SetUniformMat3("normal_matrix", glm::mat3(glm::transpose(glm::inverse(camera.view * models[i]))), false);
    lighting_shader->SetUniformMat4("model_view_matrix", camera.view * models[i], false);
    lighting_shader->SetUniformVec3("color", colors[i]);
    gl_render_system.Draw(GL_TRIANGLES, 0, test_vertices.size());
}
```

Sample Image:
![](https://github.com/xz1a/GLSandbox/blob/main/gallery/directional_shadow_mapping.JPG)