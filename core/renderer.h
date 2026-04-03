#pragma once
#include "../vendor/entt.hpp"
#include "window.h"
#include <memory>

namespace Renderer {

extern std::shared_ptr<Window> windowPtr;

void BeginDraw();
void EndDraw();

void drawMeshes(entt::registry &world);
void drawLights();

} // namespace Renderer
