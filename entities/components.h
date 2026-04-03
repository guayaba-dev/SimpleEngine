#pragma once

#include "../vendor/glm/glm.hpp"

struct TransformComponent {
  glm::mat4 modelMatrix;
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f);
  glm::vec3 scale = glm::vec3(1.0f);
};

struct MeshComponent {
  unsigned int vao;
  unsigned int vbo;
  unsigned int eao;
  int indexCount;
  int vertexCount;
  unsigned textureID;
};

struct MaterialComponent {
  unsigned int shaderID;
  unsigned int diffuseTexture;
  unsigned int specularTexuture;
  glm::vec3 ambientColor;
  float shininess;
};

struct LightComponent {
  glm::vec3 position;
  glm::vec3 color;
  float intensity;
  bool isDirectional;
};

struct CameraComponent {
  float fov = 45.0f;
  float nearPlane = 0.1f;
  float farPlane = 100.0f;
  float yaw = 0.0;
  float pitch = 0.0;
  glm::vec3 zDir = glm::vec3(0.0f);
  glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
};
