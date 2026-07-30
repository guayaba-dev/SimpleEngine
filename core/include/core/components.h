#pragma once

#include "detail/qualifier.hpp"
#include <core/pch.hpp>
#include <vector>

struct TransformComponent {
  glm::mat4 modelMatrix = glm::mat4(1.0);
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f);
  glm::vec3 scale = glm::vec3(1.0f);
};

struct Shader {
  unsigned int shaderID = 0;
};

struct PhongMaterial {
  unsigned int diffuseMap = 0;
  unsigned int specularMap = 0;
  float shininess = 32.0;
  glm::vec3 ambientColor = glm::vec3(0.1);
};

struct UnlitMaterial {
  glm::vec3 color = glm::vec3(1.f);
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
  glm::vec3 ambientColor = glm::vec3(0.0f);
};

struct LightComponent {
  float intensity = 1.0f;
  glm::vec3 color = glm::vec3(1.0f);
};

struct GPULight { // DATA SENDED TO THE GPU
  glm::vec4 position;
  glm::vec4 color;
};

struct FrameContext {
  unsigned int uboLights;
  float time = 0.0f;
  float deltaTime = 0.0f;
  glm::mat4 viewMat = glm::mat4(1.0);
  glm::mat4 projMat = glm::mat4(1.0);
  glm::vec3 camPos = glm::vec3(1.0);
  std::vector<GPULight> lights;
};

struct CameraComponent {
  float fov = 45.0f;
  float nearPlane = 0.1f;
  float farPlane = 100.0f;
  float yaw = 0.0;
  float pitch = 0.0;
  bool active = false;
  glm::vec3 zDir = glm::vec3(0.0f);
  glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
};
