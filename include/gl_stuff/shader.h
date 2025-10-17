#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>

#include <glad/glad.h>

std::string loadShaderFile(std::string path);
bool compileShader(std::string& sourceCode, unsigned int shaderType, unsigned int& shaderID);
bool getShaderError(unsigned int shaderID, std::string shaderTag);
bool getShaderProgramError(unsigned int programID);

class ShaderProgram
{
private:
    unsigned int ID;

public:

    ShaderProgram(std::string vertShaderPath, std::string fragShaderPath);
    ~ShaderProgram();

    void use();
    unsigned int getID();

    void updateFloat(std::string uniformName, float value);
    void updateInt(std::string uniformName, int value);
    void updateUInt(std::string uniformName, unsigned int value);

    void updateFVec2(std::string uniformName, float x, float y);
    void updateFVec3(std::string uniformName, float x, float y, float z);
    void updateFVec4(std::string uniformName, float x, float y, float z, float w);
};



#endif