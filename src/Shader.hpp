//
// Created by Danny Le on 2022-08-27.
//

#ifndef SPINNING_RAT_SHADER_HPP
#define SPINNING_RAT_SHADER_HPP

#pragma once
#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void Use();

    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);


private:
    unsigned int ProgramID;
};


#endif //SPINNING_RAT_SHADER_HPP
