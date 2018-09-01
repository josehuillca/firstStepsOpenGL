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
    const int num_vertex = 16;
    float positionColorData[num_vertex] = {
            -0.5f, -0.5f, 0.0f, 1.0f, //0
             0.5f, -0.5f, 0.0f, 1.0f, //1
             0.5f,  0.5f, 0.0f, 1.0f, //2
            -0.5f,  0.5f, 0.0f, 1.0f  //3
    };
    const int num_indices = 6;
    unsigned int indices[num_indices] = {
            0, 1, 3,
            1, 2, 3
    };

    unsigned int bufferPosition;
    glGenBuffers(1, &bufferPosition);
    glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
    glBufferData(GL_ARRAY_BUFFER, num_vertex* sizeof(float), positionColorData, GL_STATIC_DRAW);

    unsigned int bufferIndex;
    glGenBuffers(1, &bufferIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices* sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // very important the 'VAO-handle'
    unsigned int vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    glEnableVertexAttribArray(0);
    // assignment of the position VBO to slot 0 of VAO
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, 0);


    return bufferIndex;
}

void ShaderCode::run() {
    // creates the vertex array object. Must be performed before the shaders compilation.
    unsigned int bufferIndex = constructVertexArrayObject();

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
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndex);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader.getProgramId());

    glfwTerminate();
}

