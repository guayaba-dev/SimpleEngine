#pragma once

#include "gtc/type_ptr.hpp"
#include <core/components.h>
#include <core/pch.hpp>
#include <iostream>
#include <memory>
#include <vector>

template <typename materialComp>
bool defaultCheckBind(entt::entity entity, entt::registry &world) {
  return world.all_of<materialComp>(entity);
}

class IBinder {

public:
  virtual bool checkBind(entt::entity entity, entt::registry &world) = 0;

  virtual void bind(entt::entity entity, entt::registry &world,
                    unsigned int shaderID) = 0;
};

class MaterialManager {

public:
  void bind_FrameContex(entt::registry &world, unsigned int shaderID) {

    auto &matCtx = world.ctx().get<FrameContext>();

    // CAMERA
    glUniform3fv(glGetUniformLocation(shaderID, "viewPos"), 1,
                 glm::value_ptr(matCtx.camPos));

    // TRANSFORM MATS
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE,
                       glm::value_ptr(matCtx.viewMat));

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1,
                       GL_FALSE, glm::value_ptr(matCtx.projMat));

    // LIGHT
    if (!matCtx.lights.empty()) {

      glUniform3fv(glGetUniformLocation(shaderID, "lightPos"), 1,
                   glm::value_ptr(matCtx.lights[0].position));
      glUniform3fv(glGetUniformLocation(shaderID, "lightColor"), 1,
                   glm::value_ptr(matCtx.lights[0].color));
      glUniform1f(glGetUniformLocation(shaderID, "lightIntesity"),
                  matCtx.lights[0].intensity);
    }
  }

  void bind_object(entt::entity entity, entt::registry &world,
                   unsigned int shaderID) {

    auto &transform = world.get<TransformComponent>(entity);

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE,
                       glm::value_ptr(transform.modelMatrix));
  }

  void bind(entt::entity entity, entt::registry &world, unsigned int shaderID) {

    bind_object(entity, world, shaderID);

    for (auto &binder : materialBinders) {

      if (binder->checkBind(entity, world)) {
        binder->bind(entity, world, shaderID);
      }
    }
  }

  void addMaterialBinder(std::unique_ptr<IBinder> binder) {

    std::cerr << "[ADD_BINDER]: "
              << " System ptr: " << binder.get()
              << ", System type: " << typeid(*binder).name() << std::endl;

    materialBinders.push_back(std::move(binder));
  }

private:
  std::vector<std::unique_ptr<IBinder>> materialBinders;
};
