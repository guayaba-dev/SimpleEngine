#pragma once

#include <entt.hpp>

#include "core/SystemManager.h"
#include "core/components.h"
#include "core/meshManager.h"
#include "core/shaderManager.h"
#include "core/textureManager.h"
#include "inputManager.h"
#include "renderer.h"
#include "system.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <memory>

class Engine {

  entt::registry world;

  std::shared_ptr<Window> windowPtr;

public:
  static inline MeshManager meshMag{};
  static inline TextureManager texMag{};
  static inline ShaderManager shaderMag{};
  static inline SystemManager systemManager{};

  entt::registry &getWorld() { return world; }

  void start() {

    windowPtr = std::make_shared<Window>();

    Renderer::windowPtr = std::shared_ptr<Window>(windowPtr);

    InputManager::init(windowPtr->getWindow());

    auto cam = getWorld().create();
    getWorld().emplace<CameraComponent>(cam);
    getWorld().emplace<TransformComponent>(cam);
    getWorld().get<CameraComponent>(cam).active = true;
    Renderer::setActiveCamera(cam);

    systemManager.add_system(STAGE::POSTUPDATE,
                             std::make_unique<System::CameraSystem>());

    systemManager.add_system(STAGE::POSTUPDATE,
                             std::make_unique<System::TransformSystem>());

  }; // STARTS OPENGL PROFILE

  void run() {
    float lastTime = glfwGetTime();

    while (!windowPtr->windowShouldClose()) {

      // WINDOW LOGIC
      windowPtr->checkWindowShouldClose();
      // DELTA TIME
      float time = glfwGetTime();
      float dt = time - lastTime;
      lastTime = time;

      systemManager.update(getWorld(), dt);

      Renderer::genMatrix(world);
      Renderer::BeginDraw();
      Renderer::drawMeshes(world);
      Renderer::EndDraw();
    }
  };

  void shutDown() {}; // SHUTS DOWN ENGINE
};
