// material_binders.hpp
#pragma once
#include "core/materialHandellers.h"
#include <core/components.h>

class PhongBinder : public IBinder {

public:
  bool checkBind(entt::entity entity, entt::registry &world) {
    return defaultCheckBind<PhongMaterial>(entity, world);
  }

  void bind(entt::entity entity, entt::registry &world, unsigned int shaderID) {
    auto phongMat = world.get<PhongMaterial>(entity);

    glUniform3fv(glGetUniformLocation(shaderID, "ambientColor"), 1,
                 glm::value_ptr(phongMat.ambientColor));
    glUniform1f(glGetUniformLocation(shaderID, "specularStrength"),
                phongMat.shininess);
  }
};

class UnlitBinder : public IBinder {

public:
  bool checkBind(entt::entity entity, entt::registry &world) {
    return defaultCheckBind<UnlitMaterial>(entity, world);
  }

  void bind(entt::entity entity, entt::registry &world, unsigned int shaderID) {
  }
};
