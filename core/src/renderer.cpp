#include "fwd.hpp"
#include <core/pch.hpp>

#include <memory>

#include <core/components.h>
#include <core/materialBinders.h>
#include <core/renderer.h>
#include <core/system.h>

static glm::mat4 m_view = glm::mat4(1.f);
static glm::mat4 m_projection = glm::mat4(1.f);

std::shared_ptr<Window> Renderer::windowPtr = nullptr;

void Renderer::BeginDraw() {
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void Renderer::genMatrix(entt::registry &world) {
  auto &camera = world.ctx().get<CameraComponent>();
  auto &transform = world.ctx().get<TransformComponent>();

  m_view = System::getCameraView(camera, transform);
  m_projection = System::getCameraProjection(camera, 800.0f / 600);
}

void Renderer::EndDraw() { glfwSwapBuffers(Renderer::windowPtr->getWinow()); }

void bindMesh(const MeshComponent &mesh) {
  glBindVertexArray(mesh.vao);
  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

  if (mesh.eao != 0) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.eao);
  }
}

void drawMesh(const MeshComponent &mesh) {
  if (mesh.eao == 0) {
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    return;
  }

  glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, (void *)0);
}

void Renderer::drawMeshes(entt::registry &world) {

  auto lightComponent = world.ctx().emplace<LightComponent>();
  auto &transformComponent = world.ctx().get<TransformComponent>();

  auto view = world.view<PhongMaterial, MeshComponent, TransformComponent>();

  for (auto [entity, material, mesh, transform] : view.each()) {

    MaterialBinder::bind(material, transform.modelMatrix, m_view, m_projection,
                         transformComponent.position, lightComponent);

    bindMesh(mesh);

    drawMesh(mesh);
  };
}

void Renderer::drawLights(entt::registry &world) {}
