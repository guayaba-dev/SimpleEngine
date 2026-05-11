// material_binders.hpp
#pragma once
#include <core/components.h>

// Cada binder recibe el shaderID y los datos que necesita
namespace MaterialBinder {

inline void bind(const PhongMaterial &mat, const glm::mat4 &model,
                 const glm::mat4 &view, const glm::mat4 &proj,
                 const glm::vec3 &viewPos, const LightComponent &light) {
  glUseProgram(mat.shaderID);

  // Matrices
  glUniformMatrix4fv(glGetUniformLocation(mat.shaderID, "model"), 1, GL_FALSE,
                     glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(mat.shaderID, "view"), 1, GL_FALSE,
                     glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(mat.shaderID, "projection"), 1,
                     GL_FALSE, glm::value_ptr(proj));

  // Camera
  glUniform3fv(glGetUniformLocation(mat.shaderID, "viewPos"), 1,
               glm::value_ptr(viewPos));

  // Light
  glUniform3fv(glGetUniformLocation(mat.shaderID, "lightPos"), 1,
               glm::value_ptr(glm::vec3(0.f, 2.f, 1.f)));
  glUniform3fv(glGetUniformLocation(mat.shaderID, "lightColor"), 1,
               glm::value_ptr(light.color));

  // Material
  glUniform3fv(glGetUniformLocation(mat.shaderID, "ambientColor"), 1,
               glm::value_ptr(mat.ambientColor));
  glUniform1f(glGetUniformLocation(mat.shaderID, "shininess"), mat.shininess);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mat.diffuseMap);
  glUniform1i(glGetUniformLocation(mat.shaderID, "diffuseMap"), 0);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, mat.specularMap);
  glUniform1i(glGetUniformLocation(mat.shaderID, "specularMap"), 1);
}

inline void bind(const UnlitMaterial &mat, const glm::mat4 &model,
                 const glm::mat4 &view, const glm::mat4 &proj) {
  glUseProgram(mat.shaderID);

  glUniformMatrix4fv(glGetUniformLocation(mat.shaderID, "model"), 1, GL_FALSE,
                     glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(mat.shaderID, "view"), 1, GL_FALSE,
                     glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(mat.shaderID, "projection"), 1,
                     GL_FALSE, glm::value_ptr(proj));

  glUniform3fv(glGetUniformLocation(mat.shaderID, "color"), 1,
               glm::value_ptr(mat.color));
}

} // namespace MaterialBinder
