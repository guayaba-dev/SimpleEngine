#include "core/materialHandellers.h"
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
  renderer->drawWorld(world);
}

// OPENGL RENDERER

void OpenGLRenderer::BeginDraw() {
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void OpenGLRenderer::genMatrix(entt::registry &world) {
  auto &frameContext = world.ctx().get<FrameContext>();

  auto camView = world.view<CameraComponent>();

  activeCamera = *camView.begin();

  if (activeCamera == entt::null) {
    return;
  }

  std::shared_ptr<Window> spWindow = windowPtr.lock();

  if (!spWindow)
    return;

  auto &camera = world.get<CameraComponent>(activeCamera);
  auto &transform = world.get<TransformComponent>(activeCamera);

  std::vector<lightData> lights;
  auto lightView = world.view<LightComponent, TransformComponent>();
  for (auto [entity, light, transform] : lightView.each()) {
    lights.push_back({transform.position, light.color, light.intensity});
  }

  m_view = System::getCameraView(camera, transform);
  m_projection =
      System::getCameraProjection(camera, spWindow->getAspectRatio());
  frameContext.viewMat = m_view;
  frameContext.projMat = m_projection;
  frameContext.camPos = transform.position;
  frameContext.lights = lights;
}

void OpenGLRenderer::EndDraw() {

  std::shared_ptr<Window> spWindow = windowPtr.lock();

  if (!spWindow)
    return;

  glfwSwapBuffers(spWindow->getWindow());
}

void OpenGLRenderer::drawWorld(entt::registry &world) {
  genMatrix(world);
  unsigned int lastShader = 0xFFFFFFF;

  world.sort<Shader>([](const Shader &lhs, const Shader &rhs) {
    return lhs.shaderID < rhs.shaderID;
  });
  auto sortedView = world.view<Shader, MeshComponent>();

  for (auto [entity, shader, mesh] : sortedView.each()) {

    if (shader.shaderID != lastShader) {
      glUseProgram(shader.shaderID);
      materialManager->bind_FrameContex(world, shader.shaderID);
      lastShader = shader.shaderID;
    }

    materialManager->bind(entity, world, shader.shaderID);
    bindMesh(mesh);
    drawMesh(mesh);
  }

  ;
};
