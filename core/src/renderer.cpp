#include "fwd.hpp"
#include "gtc/type_ptr.hpp"
#include <core/pch.hpp>

#include <memory>

#include <core/components.h>
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

void bindMaterial(const MaterialComponent &material) {

  glUseProgram(material.shaderID);
}

void bindMesh(const MeshComponent &mesh) {
  glBindVertexArray(mesh.vao);
  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

  if (mesh.eao != 0) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.eao);
  }
}

void bindLights(const LightComponent &light,
                const MaterialComponent &material) {

  glUniform3fv(glGetUniformLocation(material.shaderID, "lightPos"), 1,
               glm::value_ptr(light.position));

  glUniform3fv(glGetUniformLocation(material.shaderID, "lightColor"), 1,
               glm::value_ptr(light.color));
}

void bindUniform(const MaterialComponent &material,
                 const glm::mat4 &modelMatrix) {

  glUniformMatrix4fv(glGetUniformLocation(material.shaderID, "model"), 1,
                     GL_FALSE, glm::value_ptr(modelMatrix));

  glUniformMatrix4fv(glGetUniformLocation(material.shaderID, "view"), 1,
                     GL_FALSE, glm::value_ptr(m_view));

  glUniformMatrix4fv(glGetUniformLocation(material.shaderID, "projection"), 1,
                     GL_FALSE, glm::value_ptr(m_projection));

  glUniform3fv(glGetUniformLocation(material.shaderID, "ambientColor"), 1,
               glm::value_ptr(material.ambientColor));

  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(material.shaderID, "texture1"), 0);
  glBindTexture(GL_TEXTURE_2D, material.textureID);
}

void drawMesh(const MeshComponent &mesh) {
  if (mesh.eao == 0) {
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    return;
  }

  glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, (void *)0);
}

void drawEntity(const MaterialComponent &material, const glm::mat4 &modelMatrix,
                const MeshComponent &mesh, const LightComponent &light) {

  bindMaterial(material);

  bindLights(light, material);

  bindUniform(material, modelMatrix);

  bindMesh(mesh);

  drawMesh(mesh);
}

void Renderer::drawMeshes(entt::registry &world) {

  auto view =
      world.view<MaterialComponent, MeshComponent, TransformComponent>();

  auto lightComponent = world.ctx().emplace<LightComponent>();

  for (auto [entity, material, mesh, transform] : view.each()) {
    drawEntity(material, transform.modelMatrix, mesh, lightComponent);
  };
}

void Renderer::drawLights(entt::registry &world) {}
