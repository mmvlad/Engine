#version 330 core

in vec3 in_vertex_position;
in vec4 in_vertex_color;

out vec4 vertexColor;

void main(){
    gl_Position = vec4(in_vertex_position, 1.0);

    vertexColor = in_vertex_color;
 }