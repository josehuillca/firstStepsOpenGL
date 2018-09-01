//
// Created by Jose Huillca on 9/1/18.
//

#ifndef FIRSTSTEPSOPENGL_SHADERPROGRAM_H
#define FIRSTSTEPSOPENGL_SHADERPROGRAM_H

#include <GL/glew.h>
#include <iostream>     // std::cout
#include <stdio.h>
#include <fstream>
#include <sstream>      // std::stringstream, std::stringbuf

using namespace std;

class ShaderProgram {
private:
    unsigned int programId;

    string loadFile(const string& filename);
    unsigned int loadAndCompileShader(unsigned int type, const string & source);
public:
    ShaderProgram();

    void init(const string & vertexShader, const string & fragmentShader);
    unsigned int getProgramId() const;
};


#endif //FIRSTSTEPSOPENGL_SHADERPROGRAM_H
