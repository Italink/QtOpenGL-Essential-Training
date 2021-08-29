#version 400 core
layout(points) in;
layout(points, max_vertices = 1) out;

in Particle{
    vec3  position;
    vec3  velocity;
    float size;
    float life;
    vec4  color;
}particle[];

out vec3  position;
out vec3  velocity;
out float size;
out float life;
out vec4  color;

uniform float lifetime;

void main(){
    if(particle[0].life>lifetime)
        return;
    position = particle[0].position;
    velocity = particle[0].velocity;
    size     = particle[0].size;
    life     = particle[0].life;
    color    = particle[0].color;
    EmitVertex();
    EndPrimitive();
}
