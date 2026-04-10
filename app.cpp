
#include "core/meshManager.h"
#include "detail/qualifier.hpp"
#include "fwd.hpp"
#include <core/pch.hpp>

#include <core/components.h>
#include <core/engine.h>

#include <iostream>
#include <string>

float square[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
};

float cubeVertex[] = {
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f, -0.5f,
    0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f,
    0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,

    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,
    0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,
    0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
    -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
    -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
    1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
    1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, -0.5f,
    0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,
    0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
    0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,
    0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f};

int vertexSize = sizeof(cubeVertex);
int vertexCount = vertexSize / (sizeof(float) * 6);

int main() {

  std::cerr << "vertexSize: " << vertexSize << '\n';
  std::cerr << "vertexCount: " << vertexCount << '\n';

  Engine engine = Engine();
  engine.start();

  /*
  Engine::meshMag.loadMesh("square", square, sizeof(square), squareMesh.vao,
                           squareMesh.vbo);
  squareMesh.vertexCount = vertexCount;

  MaterialComponent squareMaterial;
  squareMaterial.shaderID = Engine::shaderMag.loadShader(
      "basicShader", "assets/basic.vert", "assets/basic.frag");
  squareMaterial.textureID = Engine::texMag.loadTexture("assets/container.jpg");
*/

  MeshComponent squareMesh;
  Engine::meshMag.loadNormalMesh("cubeVertex", cubeVertex, vertexSize,
                                 squareMesh);
  squareMesh.vertexCount = vertexCount;

  MaterialComponent squareMaterial;
  squareMaterial.shaderID = Engine::shaderMag.loadShader(
      "PhongShading", "assets/phongLight.vert", "assets/phongLight.frag");
  squareMaterial.ambientColor = glm::vec3(0.6, 0.1, 0.2);

  MaterialComponent lightMaterial;
  lightMaterial.shaderID = Engine::shaderMag.loadShader(
      "LightShader", "assets/basic.vert", "assets/basic.frag");
  lightMaterial.ambientColor = glm::vec3(1.0);

  LightComponent lightComponent;
  lightComponent.color = glm::vec3(1., 1., 1.);
  lightComponent.intensity = 0.6;

  TransformComponent lightTransform;
  lightTransform.position = glm::vec3(0., 2., 1.);

  auto &registry = engine.getWorld();

  auto entity = registry.create();
  auto light = registry.create();

  registry.emplace<MeshComponent>(entity, squareMesh);
  registry.emplace<MaterialComponent>(entity, squareMaterial);
  auto &transform = registry.emplace<TransformComponent>(entity);
  transform.position = glm::vec3(0.f, 0.f, 3.0f);

  registry.emplace<MeshComponent>(light, squareMesh);
  registry.emplace<TransformComponent>(light, lightTransform);
  registry.emplace<MaterialComponent>(light, lightMaterial);

  registry.ctx().emplace<CameraComponent>();
  registry.ctx().emplace<TransformComponent>();
  registry.ctx().emplace<LightComponent>(lightComponent);

  engine.run();

  engine.shutDown();

  return 0;
}
