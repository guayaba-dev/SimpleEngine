#include <core/pch.hpp>

#include <iostream>
#include <memory>

#include <core/components.h>
#include <core/materialBinders.h>
#include <core/renderer.h>
#include <core/system.h>
#include <vector>

// DRAW UTILS

void OpenGLRenderer::bindMesh(const MeshComponent &mesh) {
  glBindVertexArray(mesh.vao);
  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

  if (mesh.eao != 0) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.eao);
  }
}

void OpenGLRenderer::drawMesh(const MeshComponent &mesh) {

  if (mesh.eao == 0) {
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    return;
  }

  glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, (void *)0);
}

// CLASS

void RenderSystem::on_update(entt::registry &world, float dt) {
  renderer->BeginDraw();
  renderer->drawMeshes(world);
  renderer->EndDraw();
}

// OPENGL RENDERER

void OpenGLRenderer::BeginDraw() {
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void OpenGLRenderer::genMatrix(entt::registry &world) {
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

void OpenGLRenderer::EndDraw() {

  std::shared_ptr<Window> spWindow = windowPtr.lock();

  if (!spWindow)
    return;

  glfwSwapBuffers(spWindow->getWindow());
}

void OpenGLRenderer::drawMeshes(entt::registry &world) {
  auto camView = world.view<CameraComponent>();
  if (camView.empty())
    return;

  activeCamera = *camView.begin();

  if (activeCamera == entt::null)
    return;

  genMatrix(world);

  std::vector<MaterialBinder::lightData> lights;
  auto lightView = world.view<LightComponent, TransformComponent>();
  for (auto [entity, light, transform] : lightView.each())
    lights.push_back({transform.position, light.color, light.intensity});

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
