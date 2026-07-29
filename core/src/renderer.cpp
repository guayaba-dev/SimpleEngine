#include "ext/vector_float4.hpp"
#include <algorithm>
#include <core/pch.hpp>

#include <iostream>
#include <memory>

#include <core/components.h>
#include <core/materialBinders.h>
#include <core/renderer.h>
#include <core/system.h>
#include <vector>

// DRAW UTILS
struct lightBlockData {
  int numLights = 0;   // 4 bytes
  int _pad[3];         // 12 bytes completes offset of 16bytes
  GPULight lights[16]; // 16 base * 16
};

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
void RenderSystem::on_start(entt::registry &world) {
  auto &frameContext = world.ctx().get<FrameContext>();

  glGenBuffers(1, &frameContext.uboLights);
  glBindBuffer(GL_UNIFORM_BUFFER, frameContext.uboLights);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(lightBlockData), NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  glBindBufferBase(GL_UNIFORM_BUFFER, 0, frameContext.uboLights);

  auto shaderView = world.view<Shader>();

  for (auto [entt, shader] : shaderView.each()) {
    glUniformBlockBinding(shader.shaderID,
                          glGetUniformBlockIndex(shader.shaderID, "LightBlock"),
                          0);
  }
};

void RenderSystem::on_update(entt::registry &world, float dt) {
  renderer->drawWorld(world);
}

// OPENGL RENDERER

void OpenGLRenderer::BeginDraw() {
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void OpenGLRenderer::genContext(entt::registry &world) {
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

  std::vector<GPULight> lights;
  auto lightView = world.view<LightComponent, TransformComponent>();
  for (auto [entity, light, transform] : lightView.each()) {
    lights.push_back(
        {glm::vec4(transform.position, 1.0f), glm::vec4(light.color, 1.0f)});
  }

  m_view = System::getCameraView(camera, transform);
  m_projection =
      System::getCameraProjection(camera, spWindow->getAspectRatio());
  frameContext.viewMat = m_view;
  frameContext.projMat = m_projection;
  frameContext.camPos = transform.position;
  frameContext.lights = lights;
}

void OpenGLRenderer::uploadUniformBuffer(entt::registry &world) {
  auto &frameContext = world.ctx().get<FrameContext>();

  lightBlockData data{};

  data.numLights = std::min((int)frameContext.lights.size(), 16);

  for (int i = 0; i < data.numLights; i++) {
    data.lights[i] = frameContext.lights[i];
  }

  glBindBuffer(GL_UNIFORM_BUFFER, frameContext.uboLights);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lightBlockData), &data);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLRenderer::EndDraw() {

  std::shared_ptr<Window> spWindow = windowPtr.lock();

  if (!spWindow)
    return;

  glfwSwapBuffers(spWindow->getWindow());
}

void OpenGLRenderer::drawWorld(entt::registry &world) {
  genContext(world);
  uploadUniformBuffer(world);
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
};
