//
// Created by Jose Huillca on 9/1/18.
//

#ifndef FIRSTSTEPSOPENGL_SHADERPROGRAM_H
#define FIRSTSTEPSOPENGL_SHADERPROGRAM_H

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include <stdio.h>
#include <fstream>

using namespace std;

class ShaderProgram {
private:
    unsigned int programId;

    unsigned int loadAndCompileShader();
public:
    ShaderProgram();

    void init();
    unsigned int getProgramId() const;
    string loadFile(string filename);
};


#endif //FIRSTSTEPSOPENGL_SHADERPROGRAM_H
