#pragma once

#include <entt.hpp>

#include "inputManager.h"
#include "renderer.h"
#include "system.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

class Engine {

  entt::registry world;

  std::shared_ptr<Window> windowPtr;

public:
  entt::registry &getWorld() { return world; }

  void start() {
    windowPtr = std::make_shared<Window>();

    Renderer::windowPtr = std::shared_ptr<Window>(windowPtr);

    InputManager::init(windowPtr->getWinow());

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

      // CAMERA MAGIC
      System::cameraInput(world.ctx().get<CameraComponent>(),
                          world.ctx().get<TransformComponent>(), dt);

      System::moveCamera(world.ctx().get<CameraComponent>());
      System::updateTransforms(dt, world);

      Renderer::BeginDraw();

      Renderer::drawMeshes(world);

      Renderer::EndDraw();
    }
  };

  void shutDown() {}; // SHUTS DOWN ENGINE
};
