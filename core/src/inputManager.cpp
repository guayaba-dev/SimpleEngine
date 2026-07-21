#include <GLFW/glfw3.h>
#include <core/inputManager.h>
#include <iostream>

#include <core/pch.hpp>

namespace InputManager {

void init(GLFWwindow *window) {
  glfwSetKeyCallback(window, KeyCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool isKeyDown(int key) { return keys[key]; }

void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  if (key >= 0 && key < 350)
    keys[key] = action != GLFW_RELEASE;
}

void toggleInputMode(GLFWwindow *window) {
  if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return;
  }

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void mouseCallback(GLFWwindow *window, double xPos, double yPos) {
  if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
    return;

  if (firstMouse) {
    mouseX = xPos;
    mouseY = yPos;
    firstMouse = false;
  }

  deltaX = xPos - mouseX;
  deltaY = yPos - mouseY;

  mouseX = xPos;
  mouseY = yPos;
}

} // namespace InputManager
