
# Blinn-Phong Lighting Model

A simple implementation of the Blinn-Phong Lighting model shader.






## Light Parameters

```
struct Light {
    int type; // 0 = directional, 1 = point, 2 = spotlight
    vec3 color;
    vec3 ambient;
    vec3 position_or_direction;
    vec3 half_vector;
    vec3 cone_direction;
    float spotlight_cut_off;
    float spotlight_exponent;
    float constant_attenuation;
    float linear_attenuation;
    float quadratic_attenuation;
};
```
## Directional Light

- Directional Lights only have a direction and have a constant halfway vector for specular lighting. The halfway vector was calculated:

```
glm::vec3 light_direction_viewspace = glm::normalize(glm::vec3(camera.view * glm::vec4(light.position_or_direction, 0.0f)));
	glm::vec3 eye_direction_viewspace = glm::normalize(glm::vec3(camera.view * glm::vec4(camera.position - camera.view_target, 0.0f)));
	light.half_vector = glm::normalize(light_direction_viewspace + eye_direction_viewspace);
```
- Cube Directional Light gif
![](https://github.com/xz1a/GLSandbox/blob/main/gallery/directional_cube.gif)
- Sphere Directional Light gif
![](https://github.com/xz1a/GLSandbox/blob/main/gallery/directional_sphere.gif)
- Torus Directional Light image
![torus](https://github.com/xz1a/GLSandbox/blob/main/gallery/directional_torus.JPG)

## Point Light

Light at a position in world space with attenuation for a range.

- Cube Point Light gif
![](https://github.com/xz1a/GLSandbox/blob/main/gallery/point_cube.gif)
- Torus Point Light gif
![](https://github.com/xz1a/GLSandbox/blob/main/gallery/directional_cube.gif)

## Spotlight

- Hard Cut Off Spotlight image
![hard cut off spotlight](https://github.com/xz1a/GLSandbox/blob/main/gallery/spotlight.JPG)