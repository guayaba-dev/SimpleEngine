#pragma once

#include "core/pch.hpp"
#include "core/system.h"
#include <memory>

using System::ISystem;

enum class STAGE { INPUT, PREUPDATE, UPDATE, POSTUPDATE, RENDER };

class SystemManager {

public:
  SystemManager() = default;

  void add_system(const STAGE stage, std::unique_ptr<ISystem> system);

  void on_start(entt::registry &world);
  void update(entt::registry &world, float dt);
  void render(entt::registry &world, float dt);
  void on_stop(entt::registry &world);

private:
  std::unordered_map<STAGE, std::vector<std::unique_ptr<ISystem>>> systems;
};
