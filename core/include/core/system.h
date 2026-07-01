#pragma once

#include "components.h"
#include <entt.hpp>

namespace System {

class ISystem {

public:
  virtual ~ISystem() = default;

  virtual void on_start(entt::registry &world) {};

  virtual void on_update(entt::registry &world, float dt) = 0;

  virtual void on_stop(entt::registry &world) {};
};

class CameraSystem : public ISystem {
  void cameraInput(CameraComponent &camera, TransformComponent &transform,
                   float dt);
  void moveCamera(CameraComponent &camera);

public:
  void on_update(entt::registry &world, float dt) override;
};

class TransformSystem : public ISystem {

  void getModelMat(TransformComponent &transform);

public:
  void on_update(entt::registry &world, float dt) override;
};

glm::mat4 getCameraView(CameraComponent &camera, TransformComponent &transform);

glm::mat4 getCameraProjection(CameraComponent &camera, float aspectRatio);

} // namespace System
