#pragma once

#include <entt.hpp>

#include "core/SystemManager.h"
#include "core/components.h"
#include "core/materialBinders.h"
#include "core/materialHandellers.h"
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

  std::shared_ptr<IRenderer> renderer;

public:
  MeshManager meshMag{};
  TextureManager texMag{};
  ShaderManager shaderMag{};
  SystemManager systemManager{};
  std::shared_ptr<MaterialManager> materialManager;
  entt::registry &getWorld() { return world; }
  std::shared_ptr<Window> getWindow() { return windowPtr; };

  Engine() {
    windowPtr = std::make_shared<Window>();
    InputManager::init(windowPtr->getWindow());
    materialManager = std::make_shared<MaterialManager>();
    renderer = std::make_shared<OpenGLRenderer>(windowPtr, materialManager);
    world.ctx().emplace<FrameContext>();
  }

  void start() {
    auto cam = getWorld().create();

    getWorld().emplace<CameraComponent>(cam);
    getWorld().emplace<TransformComponent>(cam);
    getWorld().get<CameraComponent>(cam).active = true;

    systemManager.add_system(STAGE::UPDATE,
                             std::make_unique<System::CameraSystem>());

    systemManager.add_system(STAGE::POSTUPDATE,
                             std::make_unique<System::TransformSystem>());

    systemManager.add_system(STAGE::RENDER,
                             std::make_unique<RenderSystem>(renderer));

    systemManager.on_start(world);

    materialManager->addMaterialBinder(std::make_unique<PhongBinder>());
    materialManager->addMaterialBinder(std::make_unique<UnlitBinder>());
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

      renderer->BeginDraw();
      systemManager.render(getWorld(), dt);
      renderer->EndDraw();
    }
  };

  void shutDown() { systemManager.on_stop(world); }; // SHUTS DOWN ENGINE
};
