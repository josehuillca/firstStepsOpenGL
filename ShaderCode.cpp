//
// Created by Jose Huillca on 9/1/18.
//

#include "ShaderCode.h"

ShaderCode::ShaderCode() {
    showVersionsGL = true;
    titleWindow = "First Examples OpenGL";
}

void ShaderCode::initGL() {
    /* Initialize the library */
    if (!glfwInit())
        return;

    // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, titleWindow.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        return;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* put this after of glfwMakeContextCurrent() */
    if (glewInit() != GLEW_OK){
        cout<< "Error glewInit!" <<endl;
        return;;
    }

    if (showVersionsGL){
        cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<endl;
        cout<<"GLSL version: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<endl;
    }
}

void ShaderCode::run() {
/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}