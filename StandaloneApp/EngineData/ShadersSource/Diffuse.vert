#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
out vec4 Color;
uniform vec4 col;

void main(){
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;

    Color = col;
 }