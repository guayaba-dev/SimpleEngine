#pragma once

#include <string>
#include <unordered_map>

class ShaderManager {

public:
  ShaderManager() = default;

  ~ShaderManager() = default;

  unsigned int loadShader(const std::string &name,
                          const std::string &vertexPath,
                          const std::string &fragmentPath);

  unsigned int getShader(const std::string &name);

private:
  unsigned int loadFromCache(const std::string &name);

  std::unordered_map<std::string, unsigned int> cachedShaders;
};
