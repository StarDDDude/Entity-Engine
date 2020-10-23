#pragma once


#include <GL/glew.h>
#include <iostream>

class shader
{
private:    //Functions
    std::string ParseShader(const std::string& FilePath);
    void CompileAttatchShader(GLuint ShaderID, const std::string& ShaderSource);


public:     //Data
    GLuint program;


public:     //Functions
    shader(const std::string& VS_File, const std::string& FS_File);
    ~shader();
};
