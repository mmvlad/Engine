#version 330 core

in vec3 in_vertex_position;
in vec4 in_vertex_color;

uniform mat4 in_mvp;

out vec4 vertexColor;

void main()
{
    gl_Position = in_mvp * vec4(in_vertex_position, 1.0);

    vertexColor = in_vertex_color;
}