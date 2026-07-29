
#include "core/SystemManager.h"
#include "core/inputManager.h"
#include "core/meshManager.h"
#include "core/system.h"
#include "detail/qualifier.hpp"
#include "fwd.hpp"
#include <GLFW/glfw3.h>
#include <core/pch.hpp>

#include <core/components.h>
#include <core/engine.h>

#include <iostream>
#include <memory>
#include <string>

#include "app/imguiImp.h"

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

class MovingLightSys : public System::ISystem {

  float t = 0.0;
  float r = 5.0;

public:
  void on_update(entt::registry &world, float dt) override {

    if (InputManager::isKeyDown(GLFW_KEY_UP))
      r += 1.0 * dt;
    else if (InputManager::isKeyDown(GLFW_KEY_DOWN))
      r -= 1.0 * dt;

    auto view = world.view<LightComponent, TransformComponent>();

    t += dt;

    int index = 0;

    for (auto [entity, light, transform] : view.each()) {

      transform.position = glm::vec3(r * glm::sin(t + index * 180.f),
                                     r * glm::sin(t + index * 180.f),
                                     r * glm::cos(t + index * 180.f) + 3.0);

      index++;
    }
  }
};

int main() {

  std::cerr << "vertexSize: " << vertexSize << '\n';
  std::cerr << "vertexCount: " << vertexCount << '\n';

  Engine engine = Engine();

  engine.systemManager.add_system(STAGE::UPDATE,
                                  std::make_unique<MovingLightSys>());

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
  engine.meshMag.loadNormalMesh("cubeVertex", cubeVertex, vertexSize,
                                squareMesh);
  squareMesh.vertexCount = vertexCount;

  Shader squreShader;
  squreShader.shaderID = engine.shaderMag.loadShader(
      "PhongShading", "assets/phongLight.vert", "assets/phongLight.frag");

  PhongMaterial squareMaterial;
  squareMaterial.ambientColor = glm::vec3(0.6, 0.1, 0.2);

  Shader lightMaterial;
  lightMaterial.shaderID = engine.shaderMag.loadShader(
      "LightShader", "assets/basic.vert", "assets/basic.frag");

  LightComponent lightComponent;

  TransformComponent lightTransform;
  lightTransform.position = glm::vec3(4., 4., 1.);

  auto &registry = engine.getWorld();

  auto entity = registry.create();
  auto light = registry.create();
  auto light1 = registry.create();

  registry.emplace<Shader>(entity, squreShader);
  registry.emplace<MeshComponent>(entity, squareMesh);
  registry.emplace<PhongMaterial>(entity, squareMaterial);
  auto &transform = registry.emplace<TransformComponent>(entity);
  transform.position = glm::vec3(0.f, 0.f, 3.0f);

  registry.emplace<Shader>(light, lightMaterial);
  registry.emplace<UnlitMaterial>(light);
  registry.emplace<MeshComponent>(light, squareMesh);
  registry.emplace<TransformComponent>(light, lightTransform);
  registry.emplace<LightComponent>(light, lightComponent);

  registry.emplace<Shader>(light1, lightMaterial);
  registry.emplace<UnlitMaterial>(light1);
  registry.emplace<MeshComponent>(light1, squareMesh);
  registry.emplace<TransformComponent>(light1, lightTransform);
  registry.emplace<LightComponent>(light1, lightComponent);

  engine.start();

  engine.systemManager.add_system(
      STAGE::RENDER, std::make_unique<ImGuiSystem>(engine.getWindow()));

  engine.run();

  engine.shutDown();

  return 0;
}
