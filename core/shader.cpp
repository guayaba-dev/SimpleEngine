#include "shader.h"

#include "../vendor/glad/glad.h"

Shader::Shader(const char *vertexPath, const char *framentPath) {

  std::string vShaderSrc;
  std::string fShaderSrc;
  std::ifstream vFile;
  std::ifstream fFile;

  vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vFile.open(vertexPath);
    fFile.open(framentPath);
    std::stringstream vertexSteam, fragmentSteam;

    vertexSteam << vFile.rdbuf();
    fragmentSteam << fFile.rdbuf();

    vFile.close();
    fFile.close();

    vShaderSrc = vertexSteam.str();
    fShaderSrc = fragmentSteam.str();

  } catch (std::fstream::failure) {

    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_OPENED\n"
              << "ERROR::SHADER::VERTEX::PATH" << vertexPath << "\n"
              << "ERROR::SHADER::FRAGMENT::PATH" << framentPath << "\n";
  }

  const char *vShaderCode = vShaderSrc.c_str();
  const char *fShaderCode = fShaderSrc.c_str();

  // compiling the shaders

  unsigned int fragmentShader, vertexShader;
  int success;
  char infoLog[512];

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vShaderCode, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {

    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << "\n";
  }

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {

    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << "\n";
  }

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << "\n";
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
