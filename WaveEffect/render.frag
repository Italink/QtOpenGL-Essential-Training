#version 450
uniform sampler2D wave;
uniform sampler2D background;
uniform vec2 screen_size;
uniform float depth;
in vec2 waveCoord;
out vec4 FragColor;

void main(void)
{
    float height = texture2D(wave,waveCoord).x;
    vec2 offset= vec2(1.0/screen_size.x,1.0/screen_size.y);

    float upHeight = texture2D(wave,waveCoord+vec2(0,offset.y)).x;
    float rightHeight = texture2D(wave,waveCoord+vec2(offset.x,0)).x;

    vec3 up = vec3(0,1,upHeight-height);
    vec3 right = vec3(1,0,rightHeight-height);

    vec3 normal = cross(up,right);

    vec3 view = vec3(0,0,-1);

    vec3 re = refract(view,normal,1.33);

    vec2 coordOffset = re.xy*((height+depth)/re.z);

    FragColor = texture2D(background,waveCoord+coordOffset);

}
