#include "window.hpp"

#include <cstdio>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "glad/gl.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int setup_glfw()
{
    glfwSetErrorCallback(error_callback);
    return glfwInit();
}

GLFWwindow* create_window()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Holomorph", NULL, NULL);

    if (!window) {
        return NULL;
    }

    glfwMakeContextCurrent(window);
    // Limit FPS to monitor's refresh rate.
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGL(glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        window = NULL;
    }

    return window;
}

void cleanup_glfw(GLFWwindow* window)
{
    if(window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}
