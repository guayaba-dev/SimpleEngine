#include "core/pch.hpp"
#include "core/system.h"
#include <core/SystemManager.h>
#include <iostream>
#include <memory>

using System::ISystem;

void SystemManager::add_system(const STAGE stage,
                               std::unique_ptr<ISystem> system) {

  std::cerr << "[ADD_SYSTEM] Stage: " << static_cast<int>(stage)
            << ", System ptr: " << system.get()
            << ", System type: " << typeid(*system).name() << std::endl;

  systems[stage].push_back(std::move(system));
}

void SystemManager::on_start(entt::registry &world) {

  for (STAGE s : {STAGE::INPUT, STAGE::POSTUPDATE, STAGE::PREUPDATE,
                  STAGE::UPDATE, STAGE::POSTUPDATE, STAGE::RENDER}) {

    for (auto &sys : systems[s]) {
      sys->on_start(world);
    }
  }
}

void SystemManager::update(entt::registry &world, float dt) {

  for (STAGE s : {STAGE::INPUT, STAGE::POSTUPDATE, STAGE::PREUPDATE,
                  STAGE::UPDATE, STAGE::POSTUPDATE}) {

    for (auto &sys : systems[s]) {

      sys->on_update(world, dt);
    }
  }
}

void SystemManager::on_stop(entt::registry &world) {

  for (STAGE s : {STAGE::INPUT, STAGE::POSTUPDATE, STAGE::PREUPDATE,
                  STAGE::UPDATE, STAGE::POSTUPDATE, STAGE::RENDER}) {

    for (auto &sys : systems[s]) {
      sys->on_stop(world);
    }
  }
}

void SystemManager::render(entt::registry &world, float dt) {

  for (auto &sys : systems[STAGE::RENDER])
    sys->on_update(world, dt);
}
