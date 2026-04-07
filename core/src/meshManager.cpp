#include <core/components.h>
#include <core/meshManager.h>

#include <core/pch.hpp>

void MeshManager::loadMesh(const std::string &name, const float vertices[],
                           const int vertexSize, MeshComponent &mesh) {

  glGenVertexArrays(1, &mesh.vao);
  glGenBuffers(1, &mesh.vbo);

  glBindVertexArray(mesh.vao);

  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
  glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
                        (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}

void MeshManager::loadNormalMesh(const std::string &name,
                                 const float vertices[], const int vertexSize,
                                 MeshComponent &mesh) {

  glGenVertexArrays(1, &mesh.vao);
  glGenBuffers(1, &mesh.vbo);

  glBindVertexArray(mesh.vao);

  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
  glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
                        (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}
