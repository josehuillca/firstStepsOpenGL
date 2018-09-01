//
// Created by Jose Huillca on 9/1/18.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {

}

string ShaderProgram::loadFile(const string& filename) {
    ifstream f(filename.c_str());
    if (f.is_open()) {
        stringstream buf;
        buf << f.rdbuf();
        string fileContents = buf.str();

        f.close();
        return fileContents;
    }else{
        cout<<"Error reading "<<filename<<endl;
        return "";
    }
}

void ShaderProgram::init(const string & vertexShader, const string & fragmentShader) {
    programId = glCreateProgram();
    unsigned int vs = loadAndCompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = loadAndCompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(programId, vs);
    glAttachShader(programId, fs);
    glLinkProgram(programId);
    glValidateProgram(programId);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

unsigned int ShaderProgram::loadAndCompileShader(unsigned int type, const string & source) {
    unsigned int id = glCreateShader(type);

    // load code from file into String
    const char* src = loadFile(source).c_str();
    // upload src to OpenGL and associate code with shader
    glShaderSource(id, 1, &src, nullptr);
    // compile source code into binary
    glCompileShader(id);

    int result;
    // acquire compilation status
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    // check whether compilation was successful
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length* sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cout<<"Failed to compile "<<(type == GL_VERTEX_SHADER ? 'vertex': 'fragment')<<" shader!"<<endl;
        cout<<message<<endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int ShaderProgram::getProgramId() const {
    return programId;
}
