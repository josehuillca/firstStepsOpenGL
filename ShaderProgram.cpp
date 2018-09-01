//
// Created by Jose Huillca on 9/1/18.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {

}

string ShaderProgram::loadFile(string filename) {
    FILE* f = fopen(filename.c_str(), "r");
    string buffer = "";
    if (f != NULL){
        // Determine file size
        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);

        char* where = new char[size];

        rewind(f);
        fread(where, sizeof(char), size, f);

        buffer = string(where);
        delete[] where;
    } else{
        cout<<"ERROR reading "<<filename<<endl;
    }
    return buffer;
}

void ShaderProgram::init() {

}

unsigned int ShaderProgram::loadAndCompileShader() {

}

unsigned int ShaderProgram::getProgramId() const {
    return programId;
}
