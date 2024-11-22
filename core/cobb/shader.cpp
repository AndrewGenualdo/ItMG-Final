//
// Created by andrew.genualdo on 9/10/2024.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "shader.hpp"
#include "../ew/external/glad.h"
#include <glm/glm.hpp>

cobb::Shader::Shader() {
    ID = -348235985;
}

cobb::Shader::Shader(string shaderPath) {
    load(shaderPath+".vert", shaderPath+".frag");
}

cobb::Shader::Shader(string vertexPath, string fragmentPath) {
    load(vertexPath, fragmentPath);
}

void cobb::Shader::load(string vertexPath, string fragmentPath) {
    string vertexCode, fragmentCode;

    ifstream vShaderFile, fShaderFile;

    //This enables the ifstreams to throw errors in case they don't work? I don't understand why they wouldn't already do this
    vShaderFile.exceptions( ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions( ifstream::failbit | ifstream::badbit);

    try {
        //open the files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream, fShaderStream;
        //read file contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        //close file streams
        vShaderFile.close();
        fShaderFile.close();
        //convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch(ifstream::failure e) {
        //lol successfully is spelled wrong in the guide
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY:READ" << endl;

    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    //compile the shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    //vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    //print any errors if there are some
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    //fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    //linking them
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    if(!success) { //where does success get changed from? inside the vertex/fragment shaders?
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    //clean up the memory since they are already compiled/linked to the program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void cobb::Shader::use() {
    glUseProgram(ID);
}

void cobb::Shader::setBool(const string &name, bool value) const {
    //this works this way because the gpu doesn't understand booleans, only 1 and 0s
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void cobb::Shader::setInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void cobb::Shader::setFloat(const string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void cobb::Shader::setVec2(const string &name, const glm::vec2 &value) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}

void cobb::Shader::setVec3(const string &name, const glm::vec3 &value) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void cobb::Shader::setVec4(const string &name, const glm::vec4 &value) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void cobb::Shader::setMat3(const string &name, const glm::mat3& value) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void cobb::Shader::setMat4(const string &name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

//void cobb::Shader::setTexture2D(const string &name, )