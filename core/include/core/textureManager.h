#pragma once

#include <string>
#include <unordered_map>

#define STB_IMAGE_IMPLEMENTATION

class TextureManager {

public:
  TextureManager() = default;

  unsigned int loadTexture(const std::string &path);

  ~TextureManager();

private:
  unsigned int loadFromCache(const std::string &path);

  std::unordered_map<std::string, unsigned int> cachedTextures;
};
