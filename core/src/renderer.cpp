#include <core/pch.hpp>

#include <iostream>
#include <memory>

#include <core/components.h>
#include <core/renderer.h>
#include <core/system.h>

std::shared_ptr<Window> Renderer::windowPtr = nullptr;

void Renderer::BeginDraw() {
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void Renderer::EndDraw() { glfwSwapBuffers(Renderer::windowPtr->getWinow()); }

void Renderer::drawMeshes(entt::registry &world) {

  auto &camera = world.ctx().get<CameraComponent>();
  auto &transform = world.ctx().get<TransformComponent>();

  glm::mat4 viewMat = System::getCameraView(camera, transform);
  glm::mat4 projectionMat = System::getCameraProjection(camera, 800.0f / 600);

  auto view =
      world.view<MaterialComponent, MeshComponent, TransformComponent>();

  for (auto [entity, material, mesh, transform] : view.each()) {

    glUseProgram(material.shaderID);

    glUniformMatrix4fv(glGetUniformLocation(material.shaderID, "model"), 1,
                       GL_FALSE, glm::value_ptr(transform.modelMatrix));

    glUniformMatrix4fv(glGetUniformLocation(material.shaderID, "view"), 1,
                       GL_FALSE, glm::value_ptr(viewMat));

    glUniformMatrix4fv(glGetUniformLocation(material.shaderID, "projection"), 1,
                       GL_FALSE, glm::value_ptr(projectionMat));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh.textureID);

    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

    if (mesh.eao == 0) {
      glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
      continue;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.eao);

    glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, (void *)0);
  };
}
