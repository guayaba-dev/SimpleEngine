#include "fwd.hpp"
#include <core/pch.hpp>

#include <memory>

#include <core/components.h>
#include <core/materialBinders.h>
#include <core/renderer.h>
#include <core/system.h>
#include <vector>

static glm::mat4 m_view = glm::mat4(1.f);
static glm::mat4 m_projection = glm::mat4(1.f);

std::weak_ptr<Window> Renderer::windowPtr;
entt::entity Renderer::activeCamera = entt::null;

void Renderer::setActiveCamera(entt::entity &cam) { activeCamera = cam; };

void Renderer::BeginDraw() {
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void Renderer::genMatrix(entt::registry &world) {
  if (activeCamera == entt::null)
    return;

  std::shared_ptr<Window> spWindow = windowPtr.lock();

  if (!spWindow)
    return;

  auto &camera = world.get<CameraComponent>(activeCamera);
  auto &transform = world.get<TransformComponent>(activeCamera);

  m_view = System::getCameraView(camera, transform);
  m_projection =
      System::getCameraProjection(camera, spWindow->getAspectRatio());
}

void Renderer::EndDraw() {

  std::shared_ptr<Window> spWindow = windowPtr.lock();

  if (!spWindow)
    return;

  glfwSwapBuffers(spWindow->getWindow());
}

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

  if (activeCamera == entt::null)
    return;

  std::vector<MaterialBinder::lightData> lights;
  auto lightView = world.view<LightComponent, TransformComponent>();
  for (auto [entity, light, transform] : lightView.each()) {

    lights.push_back({transform.position, light.color, light.intensity});
  }

  auto &camTransform = world.get<TransformComponent>(activeCamera);

  auto phongView =
      world.view<PhongMaterial, MeshComponent, TransformComponent>();
  for (auto [entity, material, mesh, transform] : phongView.each()) {

    MaterialBinder::bind(material, transform.modelMatrix, m_view, m_projection,
                         camTransform.position, lights);

    bindMesh(mesh);

    drawMesh(mesh);
  };

  auto view = world.view<UnlitMaterial, MeshComponent, TransformComponent>();
  for (auto [entity, material, mesh, transform] : view.each()) {

    MaterialBinder::bind(material, transform.modelMatrix, m_view, m_projection);

    bindMesh(mesh);

    drawMesh(mesh);
  };
}
