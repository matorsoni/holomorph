#ifndef HO_WINDOW_HPP
#define HO_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

int setup_glfw();

GLFWwindow* create_window();

void cleanup_glfw(GLFWwindow* window);

#endif // HO_WINDOW_HPP
