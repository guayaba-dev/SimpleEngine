#pragma once

#include "../entities/components.h"
#include "../vendor/entt.hpp"

namespace System {

void getModelMat(TransformComponent &transform);

void moveCamera(CameraComponent &camera);

glm::mat4 getCameraView(CameraComponent &camera, TransformComponent &transform);

glm::mat4 getCameraProjection(CameraComponent &camera);

void update(float deltaTime, entt::registry &world);

void updateCamera(float deltaTime, entt::registry &world);

} // namespace System
