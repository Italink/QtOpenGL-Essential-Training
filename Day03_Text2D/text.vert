attribute vec2 pos;
attribute vec2 texCoord;
varying vec2 outCoord;

void main(void)
{
    gl_Position = vec4(pos,1.0,1.0);
    outCoord = texCoord;
}
