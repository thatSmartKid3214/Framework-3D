#include <gl_stuff/shader.h>

std::string loadShaderFile(std::string path)
{
    std::string source = "";
    std::string line;

    std::ifstream file(path.c_str());

    if(!file.is_open()) 
    {
        file.close();
        return "";
    }

    while(std::getline(file, line))
    {
        source += line + "\n";
    }

    file.close();

    return source;
}

bool compileShader(std::string& sourceCode, unsigned int shaderType, unsigned int& shaderID)
{
    const char* source = sourceCode.c_str();
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);

    return getShaderError(shaderID, (shaderType == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader"));
}

bool getShaderError(unsigned int shaderID, std::string shaderTag)
{
    int success;
    char log[1024];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shaderID, 1024, NULL, log);
        std::cout << shaderTag << " -> " << "Shader Compilation failed! Error: " << log << std::endl;
        return false;
    }

    return true;
}

bool getShaderProgramError(unsigned int programID)
{
    int success;
    char log[1024];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(programID, 1024, NULL, log);
        std::cout << "Program Link Error: " << log << std::endl;
        return false;
    }

    return true;
}



ShaderProgram::ShaderProgram(std::string vertShaderPath, std::string fragShaderPath)
{
    std::string vertSource = loadShaderFile(vertShaderPath);
    std::string fragSource = loadShaderFile(fragShaderPath);

    unsigned int vertShader, fragShader;
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    compileShader(vertSource, GL_VERTEX_SHADER, vertShader);
    compileShader(fragSource, GL_FRAGMENT_SHADER, fragShader);

    ID = glCreateProgram();

    glAttachShader(ID, vertShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    if(!getShaderProgramError(ID)) 
    {
        ID = -1;
        return;
    }

}

ShaderProgram::~ShaderProgram()
{
    if(ID != -1) glDeleteProgram(ID);
}

void ShaderProgram::use()
{
    glUseProgram(ID);
}

unsigned int ShaderProgram::getID()
{
    return ID;
}

void ShaderProgram::updateFloat(std::string uniformName, float value)
{
    int location = glGetUniformLocation(ID, uniformName.c_str());
    glUniform1f(location, value);
}

void ShaderProgram::updateInt(std::string uniformName, int value)
{
    int location = glGetUniformLocation(ID, uniformName.c_str());
    glUniform1i(location, value);
}

void ShaderProgram::updateUInt(std::string uniformName, unsigned int value)
{
    int location = glGetUniformLocation(ID, uniformName.c_str());
    glUniform1ui(location, value);
}

void ShaderProgram::updateFVec2(std::string uniformName, float x, float y)
{
    int location = glGetUniformLocation(ID, uniformName.c_str());
    glUniform2f(location, x, y);
}

void ShaderProgram::updateFVec3(std::string uniformName, float x, float y, float z)
{
    int location = glGetUniformLocation(ID, uniformName.c_str());
    glUniform3f(location, x, y, z);
}

void ShaderProgram::updateFVec4(std::string uniformName, float x, float y, float z, float w)
{
    int location = glGetUniformLocation(ID, uniformName.c_str());
    glUniform4f(location, x, y, z, w);
}