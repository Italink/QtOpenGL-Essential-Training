#ifdef GL_ES
precision mediump float;
#endif

// glslsandbox uniforms
uniform float time;
uniform vec2 resolution;

vec3 outCol = vec3 (.0);

void yonatansFractal (float t, vec2 FC, vec2 r, inout vec3 o)
{
    float g=0., e, s, k = t*.2;
    for(float i=0.; i < 59.;++i) {
        vec3 p = vec3(g*(FC.xy - .5*r)/r.y + .2,g - 1.);
        p.xz *= mat2(cos(k),sin(k),-sin(k),cos(k));
        s = 3.;
        for(int i=0; i < 4; ++i ) {
            s *= e = max(1.,(11.-2.*cos(k))/dot(p,p*5.));
            p = vec3(2,4,.1) - abs(abs(p)*e - vec3(4,4,2) );
        }
        g += min(length(p.xz), p.y)/s;
        o.rg += (s + .9, 11.3, s/5e4);
    }
}

void main(void)
{
    yonatansFractal(time+50., gl_FragCoord.xy, resolution.xy, outCol);
    gl_FragColor = vec4(outCol + gl_FragCoord.xyz/resolution.xyy*0.12, 1.)*vec4(0.7,1.5,0,1);
}
