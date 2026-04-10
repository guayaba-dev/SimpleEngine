#pragma once

#include "ext/matrix_float4x4.hpp"
#include "ext/vector_float3.hpp"
#include <core/pch.hpp>

struct TransformComponent {
  glm::mat4 modelMatrix = glm::mat4(1.0);
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f);
  glm::vec3 scale = glm::vec3(1.0f);
};

struct PhongComponent {
  unsigned int diffuseMap;
  unsigned int specularMap;
  glm::vec3 diffuseColor;
  glm::vec3 specularColor;
  float shininess;
};

struct MeshComponent {
  unsigned int vao = 0;
  unsigned int vbo = 0;
  unsigned int eao = 0;
  int indexCount = 0;
  int vertexCount = 0;
};

struct MaterialComponent {
  unsigned int shaderID = 0;
  unsigned int diffuseTexture = 0;
  unsigned int specularTexuture = 0;
  unsigned int textureID = 0;
  float shininess = 0;
  glm::vec3 ambientColor = glm::vec3(0);
};

struct LightComponent {
  glm::vec3 color;
  float intensity;
  float radius;
  unsigned int shadowMap;
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
