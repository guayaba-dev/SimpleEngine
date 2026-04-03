#include "system.h"

#include "../inputManager.h"

#include "../../vendor/glm/gtc/matrix_transform.hpp"
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include "../../vendor/glm/gtx/string_cast.hpp"

#include <GLFW/glfw3.h>

namespace System {

void moveCamera(CameraComponent &camera) {

  camera.yaw -= InputManager::deltaX;
  camera.pitch -= InputManager::deltaY;

  camera.pitch = (camera.pitch >= 89.0f) ? 89.0f : camera.pitch;
  camera.pitch = (camera.pitch <= -89.0f) ? -89.0f : camera.pitch;

  InputManager::deltaX = 0;
  InputManager::deltaY = 0;
}

glm::mat4 getCameraView(CameraComponent &camera,
                        TransformComponent &transform) {

  glm::mat4 view;

  camera.zDir.x =
      glm::sin(glm::radians(camera.yaw)) * glm::cos(glm::radians(camera.pitch));
  camera.zDir.y = glm::sin(glm::radians(camera.pitch));
  camera.zDir.z =
      glm::cos(glm::radians(camera.yaw)) * glm::cos(glm::radians(camera.pitch));

  view = glm::lookAt(transform.position, camera.zDir + transform.position,
                     camera.up);

  return view;
}

glm::mat4 getCameraProjection(CameraComponent &camera, float aspectRatio) {

  glm::mat4 perspective = glm::perspective(camera.fov, aspectRatio,
                                           camera.nearPlane, camera.farPlane);

  return perspective;
}

void getModelMat(TransformComponent &transform) {

  glm::mat4 rotacion = glm::mat4(1.0f);
  rotacion =
      glm::rotate(rotacion, transform.rotation.x, glm::vec3(1, 0, 0)); // pitch
  rotacion =
      glm::rotate(rotacion, transform.rotation.y, glm::vec3(0, 1, 0)); // yaw
  rotacion =
      glm::rotate(rotacion, transform.rotation.z, glm::vec3(0, 0, 1)); // roll

  glm::mat4 model = glm::identity<glm::mat4>();

  model = glm::translate(glm::mat4(1.0f), transform.position) * rotacion *
          glm::scale(glm::mat4(1.0f), transform.scale);

  transform.modelMatrix = model;
}

void updateCamera(float deltaTime, entt::registry &world) {

  auto view = world.view<CameraComponent, TransformComponent>();

  for (auto [entity, camera, transform] : view.each()) {

    moveCamera(camera);
  }
}

void updateTransforms(float deltaTime, entt::registry &world) {

  auto view = world.view<TransformComponent>();

  for (auto [entity, transform] : view.each()) {
    getModelMat(transform);
  }
}

} // namespace System
