//
// Created by Danny Le on 2022-08-27.
//
#pragma once
#include "Shader.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad.h>


Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
    //fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
    try
    {
       vShaderFile.open(vertexPath);
       fShaderFile.open(fragmentPath);
       std::stringstream  vShaderStream, fShaderStream;

       vShaderStream << vShaderFile.rdbuf();
       fShaderStream << fShaderFile.rdbuf();

       vShaderFile.close();
       fShaderFile.close();

       vertexCode = vShaderStream.str();
       fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ::" << vertexPath << "::" << fragmentPath << std::endl;
    }
    const char* vShaderCode= vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vertex);
    glAttachShader(ProgramID, fragment);
    glLinkProgram(ProgramID);

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ProgramID, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(ProgramID);
}