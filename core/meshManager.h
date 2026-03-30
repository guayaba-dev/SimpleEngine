#pragma once

#include <string>
#include <unordered_map>

class MeshManager {

public:
  MeshManager() = default;

  ~MeshManager() = default;

  // unsigned int loadMesh(std::string &path);
  void loadMesh(const std::string &name, const float vertices[],
                const int vertexCount, unsigned &vao, unsigned int &vbo);

private:
  unsigned int loadFromCache(std::string &name);

  std::unordered_map<std::string, unsigned int> cachedMeshes;
  // std::unordered_map<std::string, unsigned int> cachedMeshes;
};
