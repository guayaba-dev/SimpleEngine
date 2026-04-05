#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>
#include <string>

class Shader {

public:
  unsigned int ID;

  Shader(const char *vertexPath,
         const char *framentPath); // Defined outside the class

  void use() // use shader
  {
    glUseProgram(ID);
  }
  // utility uniform functions
  void setBool(const std::string name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  };
  void setDouble(const std::string name, double value) const {

    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  void setInt(const std::string name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
};

#endif
