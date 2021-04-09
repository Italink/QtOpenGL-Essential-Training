#version 450
#define MAX_SIZE 50
uniform vec3 mouse[50];
uniform int size;
uniform float frequency;    //频率
uniform float amplitude;    //最大振幅
uniform float wave_width;   //波纹的宽度
uniform float speed;        //水纹的移动速度
out float outHeight;

void main(void)
{
    outHeight = 0;
    for(int i=0;i<size;i++)
    {
        float time = mouse[i].z;    //鼠标点击后的时间
        float dis = distance(mouse[i].xy,gl_FragCoord.xy);  //鼠标位置到当前片段位置的距离
        float amplit = amplitude*pow(2.74,-(dis-time*speed)*(dis-time*speed)/2/(wave_width*wave_width))*sin(dis*frequency);      //计算当前片段的振幅：这里利用高斯函数突出显示当前时间所显示的波形
        outHeight += (1.0-time)*amplit*sin(dis*frequency);              //当前波形的高度
    }
}
