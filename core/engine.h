#pragma once

#include "../vendor/entt.hpp"
#include "renderer.h"
#include "window.h"
#include <memory>

class Engine {

  entt::registry world;

  std::shared_ptr<Window> windowPtr;

  // TODO RENDERER

public:
  void start() {
    windowPtr = std::make_shared<Window>();
    Renderer::windowPtr = std::shared_ptr<Window>(windowPtr);

  }; // STARTS OPENGL PROFILE

  void run() {

    // WHILE(window.should'tClose)
    // CAMERA MAGIC
    // BEGINDRAW;
    // DRAWOBJECTS;
    // DRAWLIGHTS;
    // ENDDRAWING;

  };

  void shutDown(); // SHUTS DOWN ENGINE
};
