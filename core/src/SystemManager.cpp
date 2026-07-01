#include "core/pch.hpp"
#include "core/system.h"
#include <core/SystemManager.h>
#include <memory>

using System::ISystem;

void SystemManager::add_system(const STAGE stage,
                               std::unique_ptr<ISystem> system) {
  systems[stage].push_back(std::move(system));
}

void SystemManager::on_start(entt::registry &world) {

  for (STAGE s : {STAGE::INPUT, STAGE::POSTUPDATE, STAGE::PREUPDATE,
                  STAGE::POSTUPDATE, STAGE::RENDER}) {

    for (auto &sys : systems[s]) {
      sys->on_start(world);
    }
  }
}

void SystemManager::update(entt::registry &world, float dt) {

  for (STAGE s : {STAGE::INPUT, STAGE::POSTUPDATE, STAGE::PREUPDATE,
                  STAGE::POSTUPDATE, STAGE::RENDER}) {

    for (auto &sys : systems[s]) {
      sys->on_update(world, dt);
    }
  }
}

void SystemManager::on_stop(entt::registry &world) {

  for (STAGE s : {STAGE::INPUT, STAGE::POSTUPDATE, STAGE::PREUPDATE,
                  STAGE::POSTUPDATE, STAGE::RENDER}) {

    for (auto &sys : systems[s]) {
      sys->on_stop(world);
    }
  }
}
