#pragma once
#include "window.h"
#include <entt.hpp>
#include <memory>

namespace Renderer {

extern std::shared_ptr<Window> windowPtr;
extern entt::entity activeCamera;

void BeginDraw();
void EndDraw();

void genMatrix(entt::registry &world);
void drawMeshes(entt::registry &world);
void setActiveCamera(entt::entity &cam);
} // namespace Renderer
