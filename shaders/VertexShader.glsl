#version 330 core

layout(location = 0) in vec4 position;
uniform vec2 pos;
uniform float size;
uniform float view;

void main(){
    vec4 transform = position;
    transform = transform * vec4(size, size, 1.0f, 1.0f);       //Model
    transform = transform + vec4(pos, 1.0f,0.0f);               //Position
    transform = transform / vec4(view, view, 1.0f, 1.0f);   //View

    gl_Position = transform;

}