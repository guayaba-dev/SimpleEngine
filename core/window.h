#pragma once

#include <GLFW/glfw3.h>

class Window {

  int width = 800, height = 600;

  GLFWwindow *window;
  void setProfile();
  void createWindow();
  void setGLAD();
  void setCallBacks();

public:
  Window(int width = 800, int height = 600);

  static void windowSizeCallBack(GLFWwindow *window, int width, int height);
};
