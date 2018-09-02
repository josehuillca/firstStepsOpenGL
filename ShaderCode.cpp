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
    const int num_vertex = 48;
    float vertex_attributes[num_vertex] = {
            -0.5f, -0.5f, 0.0f, 1.0f, //0 <-- X,Y,Z,W
            0.0f,  0.0f, 1.0f, 1.0f, //1  -- R,G,B,A
             0.5f, -0.5f, 0.0f, 1.0f, //2 <-- X,Y,Z,W
            0.0f,  0.0f, 1.0f, 1.0f, //3  -- R,G,B,A
            -0.5f,  0.5f, 0.0f, 1.0f, //4 <-- X,Y,Z,W
            0.0f,  0.0f, 1.0f, 1.0f, //5  -- R,G,B,A
             0.5f, -0.5f, 0.0f, 1.0f, //6 <-- X,Y,Z,W
            0.0f,  0.0f, 1.0f, 1.0f, //7  -- R,G,B,A
            -0.5f,  0.5f, 0.0f, 1.0f, //8 <-- X,Y,Z,W
            0.0f,  0.0f, 1.0f, 1.0f, //9  -- R,G,B,A
             0.5f,  0.5f, 0.0f, 1.0f, //10 <-- X,Y,Z,W
            0.0f,  0.0f, 1.0f, 1.0f, //11  -- R,G,B,A
    };

    // Indices with triangles shape
    const int num_indices = 6;
    unsigned int indices[num_indices] = {
            0, 2, 4,
            6, 8, 10
    };
    unsigned int indicesColor[num_indices] = {
            1, 3, 5,
            7, 9, 11
    };

    unsigned int attrSize  = 8*sizeof(float); // 8 -> x, y, z, w, R, G, B, A
    unsigned int colorOffs = 4*sizeof(float);

    unsigned int bufferPosition;
    glGenBuffers(1, &bufferPosition);
    glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
    glBufferData(GL_ARRAY_BUFFER, num_vertex* sizeof(float), vertex_attributes, GL_STATIC_DRAW);

    unsigned int bufferIndex;
    glGenBuffers(1, &bufferIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices* sizeof(unsigned int), indices, GL_STATIC_DRAW);

    unsigned int bufferIndexColor;
    glGenBuffers(1, &bufferIndexColor);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndexColor);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices* sizeof(unsigned int), indicesColor, GL_STATIC_DRAW);

    // very important the 'VAO-handle'
    unsigned int vaoHandle;
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndexColor);
    // assignment of the position VBO to slot 0 of VAO
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndex);
    // assignment of the position VBO to slot 0 of VAO
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, 0);
    glEnableVertexAttribArray(0);

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

