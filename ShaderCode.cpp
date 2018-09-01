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

unsigned int ShaderCode::constructVertexArrayObject() {
    float positionData[6] = {
            -0.5, -0.5,
            0.0,  0.5,
            0.5, -0.5
    };
    unsigned int bufferPosition;
    glGenBuffers(1, &bufferPosition);
    glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
    glBufferData(GL_ARRAY_BUFFER, 6* sizeof(float), positionData, GL_STATIC_DRAW);

    // very important the 'VAO-handle'
    unsigned int vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    return vaoHandle;
}

void ShaderCode::run() {
    // creates the vertex array object. Must be performed before the shaders compilation.
    unsigned int vaoHandle = constructVertexArrayObject();

    // compile and link vertex and fragment shaders into
    // a "program" that resides in the OpenGL driver
    ShaderProgram shader;
    shader.init("Shaders/simple.vert","Shaders/simple.frag");
    glUseProgram(shader.getProgramId());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vaoHandle);
        glEnableVertexAttribArray(0);

        // draw VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

