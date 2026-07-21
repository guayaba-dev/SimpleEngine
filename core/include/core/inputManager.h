#pragma once

#include "pch.hpp"

namespace InputManager {

inline bool keys[350];
inline bool mouseBTN[3];
inline bool modsArray[4];
inline double mouseX, mouseY, deltaX, deltaY;
inline bool firstMouse = true;

void init(GLFWwindow *window);

bool isKeyDown(int key);

void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods);

void mouseCallback(GLFWwindow *window, double xPos, double yPos);

void toggleInputMode(GLFWwindow *window);

} // namespace InputManager
