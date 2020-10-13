#include "shader.h"

#include "GLAssert.h"
#include <fstream>
#include <string>
#include <sstream>

shader::shader(const std::string& VS_File, const std::string& FS_File)
{
    program = glCreateProgram();
    GLuint VS_ID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FS_ID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string VS_src = ParseShader(VS_File);
    std::string FS_src = ParseShader(FS_File);
    CompileLinkShader(VS_ID, VS_src);
    CompileLinkShader(FS_ID, FS_src);

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(VS_ID));
    GLCall(glDeleteShader(FS_ID));

    GLCall(glUseProgram(program));
}

shader::~shader()
{
}

std::string shader::ParseShader(const std::string& FilePath){
    std::ifstream stream(FilePath);
    std::string line;
    std::string src;
    std::stringstream file;
    GLuint ShaderID;

    while (getline(stream, line)){
        file << line << '\n';
    }
    src = file.str();

    return src;
}

void shader::CompileLinkShader(GLuint ShaderID, const std::string& i_ShaderSource){
    const char* ShaderSource = i_ShaderSource.c_str();

    GLCall(glShaderSource(ShaderID, 1, &ShaderSource, nullptr));
    GLCall(glCompileShader(ShaderID));

    //ERROR HANDLING
    int result;
    GLCall(glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE){
        int lenght;
        GLCall(glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &lenght));
        char* message = (char*)alloca(lenght * sizeof(char));
        GLCall(glGetShaderInfoLog(ShaderID, lenght, &lenght, message));

        std::cout << "Shader failed to compile" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(ShaderID);
    }

    GLCall(glAttachShader(program, ShaderID));
}