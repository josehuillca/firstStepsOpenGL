//
// Created by Jose Huillca on 9/1/18.
//

#ifndef FIRSTSTEPSOPENGL_SHADERCODE_H
#define FIRSTSTEPSOPENGL_SHADERCODE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderProgram.h"

using  namespace std;

class ShaderCode {
private:
    bool showVersionsGL;
    string titleWindow;

    GLFWwindow* window;
public:
    ShaderCode();

    void initGL();
    void run();
};


#endif //FIRSTSTEPSOPENGL_SHADERCODE_H
