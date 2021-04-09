#version 450
layout(location=0) in vec2 pos;
out vec2 waveCoord;
void main(void)
{
    gl_Position = vec4(pos,0.0,1.0);
    waveCoord = (pos+vec2(1))/2;
}
