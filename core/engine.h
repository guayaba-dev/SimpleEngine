#pragma once

#include "../vendor/entt.hpp"
#include "window.h"

class Engine {

  entt::entity world;

  Window window;

  // TODO RENDERER

public:
  void start() { window = Window(); }; // STARTS OPENGL PROFILE

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
