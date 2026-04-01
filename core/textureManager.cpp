#include "textureManager.h"
#include "../vendor/glad/glad.h"
#include "../vendor/stb_image.h"
#include <GL/gl.h>
#include <iostream>
#include <string>

unsigned int TextureManager::loadFromCache(const std::string &path) {
  auto res_find = cachedTextures.find(path);

  if (res_find != cachedTextures.end())
    return cachedTextures.at(path);

  return 0;
}

unsigned int TextureManager::loadTexture(const std::string &path) {

  unsigned int textureID = loadFromCache(path);

  if (textureID != 0)
    return textureID;

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  int width, height, rchanells;

  unsigned char *data = stbi_load(path.c_str(), &width, &height, &rchanells, 4);

  if (!data) {
    std::cerr << "ERROR::TEXTUREMANAGER::loadTexture::" << path;
    return 0;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, GL_FALSE, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  cachedTextures.emplace(path, textureID);

  return textureID;
};

TextureManager::~TextureManager() {

  for (auto &par : cachedTextures) {

    if (par.second == 0)
      continue;

    glDeleteTextures(1, &par.second);
    par.second = 0;
  }

  cachedTextures.clear();
}
