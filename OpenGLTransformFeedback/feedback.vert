#version 400 core
layout(location = 0) in float inValue;
out OUT{
    float value;
}vs_out;

void main(void)
{
   vs_out.value=inValue;

}
