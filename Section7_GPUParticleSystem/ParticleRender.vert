#version 400

layout(location = 0) in vec3 position;
layout(location = 2) in float size;
layout(location = 4) in vec4 color;

uniform mat4 VP;

out vec4 outColor;

void main(){
    gl_Position  = VP * vec4(position,1.0);
    gl_PointSize = size ;
    outColor     = color;
}
