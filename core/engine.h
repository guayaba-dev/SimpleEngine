#pragma once

#include "../vendor/entt.hpp"
#include "renderer.h"
#include "window.h"
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

  }; // STARTS OPENGL PROFILE

  void run() {

    while (!windowPtr->windowShouldClose()) {

      // CAMERA MAGIC
      Renderer::BeginDraw();

      Renderer::drawMeshes(world);

      // DRAWLIGHTS;
      Renderer::EndDraw();
    }
  };

  void shutDown() {}; // SHUTS DOWN ENGINE
};
