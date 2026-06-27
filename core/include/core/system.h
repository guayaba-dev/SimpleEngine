#pragma once

#include "components.h"
#include <entt.hpp>

namespace System {

class ISystem {

public:
  virtual void on_start(entt::registry &world) = 0;

  virtual void on_update(entt::registry &world, float dt) = 0;

  virtual void on_stop(entt::registry &world) = 0;
};

void getModelMat(TransformComponent &transform);

void moveCamera(CameraComponent &camera);

void cameraInput(CameraComponent &camera, TransformComponent &transform,
                 float dt);

glm::mat4 getCameraView(CameraComponent &camera, TransformComponent &transform);

glm::mat4 getCameraProjection(CameraComponent &camera, float aspectRatio);

void updateTransforms(float deltaTime, entt::registry &world);

void updateCamera(float deltaTime, entt::registry &world);

} // namespace System
