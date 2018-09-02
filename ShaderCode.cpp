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
    const int num_vertex = 64;
    float vertex_attributes[num_vertex] = {
            // x,   y,    z,    w       r,      g,      b,  a
            -0.5f,  0.5f, 0.0f, 1.0f,   0.0f,  0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f,   0.0f,  0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f,   0.0f,  0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f,   0.0f,  0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f,   1.0f,  1.0f, 0.0f, 1.0f,
             0.5f,  0.5f, 0.0f, 1.0f,   1.0f,  1.0f, 0.0f, 1.0f,
             0.5f,  0.5f, 0.0f, 1.0f,   1.0f,  1.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,   1.0f,  1.0f, 0.0f, 1.0f
    };
    // VBO
    unsigned int bufferPosition;
    glGenBuffers(1, &bufferPosition);
    glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
    glBufferData(GL_ARRAY_BUFFER, num_vertex* sizeof(float), vertex_attributes, GL_STATIC_DRAW);

    // The sizes of the vertex and color components
    unsigned int vertexSize  = 4*sizeof(float);
    unsigned int colorSize = 4*sizeof(float);

    // The 'stride' is the sum of the sizes of individual components
    unsigned int stride = vertexSize + colorSize;
    // The 'offset is the number of bytes from the start of the tuple
    unsigned long offsetPosition = 0;
    unsigned long offsetColor    = 4 * sizeof(float);

    // very important the 'VAO-handle'
    unsigned int vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    // assignment of the position VBO to slot 0 of VAO
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid *)(offsetPosition));
    // assignment of the color VBO to slot 0 of VAO
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid *)(offsetColor));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

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

        // draw VAO
        glDrawArrays(GL_LINES, 0, 8);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader.getProgramId());

    glfwTerminate();
}

