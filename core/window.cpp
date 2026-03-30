#pragma once

#include "../vendor/glad/glad.h"

#include <GLFW/glfw3.h>
#include <iostream>

#include "window.h"

Window::Window(int width, int height) {
  glfwInit();
  setProfile();
  createWindow();
  glfwMakeContextCurrent(window);
  setGLAD();
  glViewport(width, height, 0, 0);
  setCallBacks();
}

void Window::createWindow() {
  window = glfwCreateWindow(width, height, "GAME-ENGINE", NULL, NULL);

  if (!window)
    std::cerr << "WINDOW::ERROR::WINDOW_CREATION\n";
}

void Window::setProfile() {

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  std::cerr << "check setProfile\n";
}

void Window::setGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "WINDOW::ERROR::UNABLE_TO_INITIATE_GLAD\n";
  }
}

void Window::setCallBacks() {
  glfwSetWindowSizeCallback(window, Window::windowSizeCallBack);
}

void Window::windowSizeCallBack(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
