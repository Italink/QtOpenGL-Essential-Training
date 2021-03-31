uniform sampler2D texture;
varying vec2 outCoord;

void main(void)
{
    gl_FragColor = texture2D(texture,outCoord);
}
