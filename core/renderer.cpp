#include "../vendor/entt.hpp"
#include "../vendor/glad/glad.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "../entities/components.h"
#include "renderer.h"

std::shared_ptr<Window> Renderer::windowPtr = nullptr;

void Renderer::BeginDraw() {
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void Renderer::EndDraw() { glfwSwapBuffers(Renderer::windowPtr->getWinow()); }

void Renderer::drawMeshes(const entt::registry &world) {

  auto view = world.view<MaterialComponent, MeshComponent>();

  for (auto [entity, material, mesh] : view.each()) {

    glUseProgram(material.shaderID);

    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh.textureID);

    if (mesh.eao == 0) {
      glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
      continue;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.eao);

    glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, (void *)0);
  };
}
