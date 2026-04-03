#include <core/meshManager.h>

#include <core/pch.hpp>

void MeshManager::loadMesh(const std::string &name, const float vertices[],
                           const int vertexCount, unsigned int &vao,
                           unsigned int &vbo) {

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 5, vertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
                        (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}
