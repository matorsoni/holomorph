#include <stdio.h>
#include <stdlib.h>

#include "glad/gl.h"

#include "window.h"

int main(void)
{
    if (!setup_glfw()) {
        fprintf(stderr, "Error: Failed to init GLFW.\n");
        return EXIT_FAILURE;
    }

    GLFWwindow* window = create_window();
    if (!window) {
        fprintf(stderr, "Error: Failed to create window with OpenGL context.\n");
        cleanup_glfw(window);
        return EXIT_FAILURE;
    }

    glClearColor(1.0, 0.5, 0.2, 1.0);

    float vertices[] = {
        0.5f, -0.5f,
        0.0f, 0.5f,
        -0.5f, -0.5f
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);

    const char* vertex_shader_src = R"(
        #version 430

        layout (location = 0) in vec2 i_pos;

        void main()
        {
            gl_Position = vec4(i_pos.xy, 0.0, 1.0);
        }
    )";

    const char* fragment_shader_src = R"(
        #version 430

        out vec4 o_color;

        void main()
        {
            o_color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, & vertex_shader_src, NULL);
    glCompileShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, & fragment_shader_src, NULL);
    glCompileShader(fragment_shader);

    // Check if shaders compiled correctly.
    {
        GLint compiled;
        GLsizei log_length = 0;
        GLchar message[1024];

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE) {
            glGetShaderInfoLog(vertex_shader, 1024, &log_length, message);
            fprintf(stderr, "Error: Vertex shader compilation failed:\n%s\n", message);
        }

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE) {
            glGetShaderInfoLog(fragment_shader, 1024, NULL, message);
            fprintf(stderr, "Error: Fragment shader compilation failed:\n%s\n", message);
        }
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    {
        GLint program_linked;
        glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
        if (program_linked != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetProgramInfoLog(program, 1024, &log_length, message);
            fprintf(stderr, "Error: Program linking failed:\n%s\n", message);
        }
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);


    glBindVertexArray(vao);
    glUseProgram(program);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    cleanup_glfw(window);
    return EXIT_SUCCESS;
}
