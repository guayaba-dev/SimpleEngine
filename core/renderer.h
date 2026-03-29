#pragma once
#include "../vendor/entt.hpp"
#include "window.h"
#include <memory>

namespace Renderer {

extern std::shared_ptr<Window> windowPtr;

void BeginDraw();
void EndDraw();

void drawMeshes(const entt::registry &world);
void drawLights();

} // namespace Renderer
