#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in mat4 aOffset;

out vec3 fColor;

void main()
{
    gl_Position = aOffset*vec4(aPos,1.0,1.0);
    fColor = aColor;
}
