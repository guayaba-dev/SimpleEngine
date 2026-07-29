#pragma once
#include "core/materialHandellers.h"
#include "core/system.h"
#include "window.h"
#include <entt.hpp>
#include <memory>

class IRenderer {

public:
  virtual void BeginDraw() = 0;
  virtual void EndDraw() = 0;
  virtual void drawWorld(entt::registry &world) = 0;
};

class OpenGLRenderer : public IRenderer {

private:
  glm::mat4 m_view = glm::mat4(1.f);
  glm::mat4 m_projection = glm::mat4(1.f);

  std::weak_ptr<Window> windowPtr;
  entt::entity activeCamera = entt::null;
  std::shared_ptr<MaterialManager> materialManager;

  void bindMesh(const MeshComponent &mesh);
  void drawMesh(const MeshComponent &mesh);
  void genContext(entt::registry &world);
  void uploadUniformBuffer(entt::registry &world);

public:
  explicit OpenGLRenderer(std::weak_ptr<Window> inWindowPtr,
                          std::shared_ptr<MaterialManager> inMaterialManager)
      : windowPtr(inWindowPtr), materialManager(std::move(inMaterialManager)) {}

  void BeginDraw() override;
  void EndDraw() override;
  void drawWorld(entt::registry &world) override;
};

class RenderSystem : public System::ISystem {

  std::shared_ptr<IRenderer> renderer;

public:
  RenderSystem(std::shared_ptr<IRenderer> renderer) : renderer(renderer) {};

  void on_start(entt::registry &world) override;

  void on_update(entt::registry &world, float dt) override;
};
