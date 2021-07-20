#version 400 core

layout(points) in;
layout(points, max_vertices = 4) out;

in OUT{
    float value;
}vs_in[];

out float outValue;

void main(){
    outValue=1.0;
    EmitVertex();
    outValue=vs_in[0].value+2;
    EmitVertex();
    outValue=vs_in[0].value+3;
    EmitVertex();
    outValue=vs_in[0].value+4;
    EmitVertex();
    EndPrimitive();
}

