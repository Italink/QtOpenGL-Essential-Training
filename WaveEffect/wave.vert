#version 450
layout(location=0) in vec2 pos;

void main(void)
{
    gl_Position = vec4(pos,0.0,1.0);
}
