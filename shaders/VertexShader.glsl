#version 330 core

layout(location = 0) in vec4 position;
uniform vec2 Pos;

void main(){

    gl_Position = position + vec4(Pos, 0.0f,0.0f);

}