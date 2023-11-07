/*
    A tiny voxel renderer in only 480 chars.

    You can turn the camera with the mouse.
    The level of detail is adjustable!
    Just change z = 8. to another power of 2,
    and break the loop at z<=POWER_OF_2.

    Can you find any improvements?
*/

uniform sampler2D texture2;
uniform float     iTime;

#define V vec3
#define m(p) (length(mod(p,4.)-2.)-2.)
#define R mat2(cos(vec4(0,11,33,0)+c

void main()
{
    vec2 I = gl_TexCoord[0].xy;
    vec2 iResolution = vec2(400.0, 300.0);

    V a = iResolution, b=V(iMouse),
    c = 3.*(b/a-.5)*sign(b),
    d = V(a.y,I+I-a.xy),
    p = V(iTime,0,0);
    d.xz *= R.y)); d.xy *= R.x));
    d /= length(d);
   
    c = p;
    float i=0.,z = 8.;
    for(;i++<1e3 && z<9.;)
    {
        a = sign(d);
        b = fract(-c*z*a);
        b += step(b,-b);
        a *= b/d;
        b = min(a.xxx,min(a.y,a.z));
        c += d*b/z;
        z *= m(a=ceil(c*z+d*step(a,b))/z-.5/z)*z<.8?2.:1.;
    }

    gl_FragColor = (sin(a.x+V(0,2,4))+1.)*(m(c)/z*2e2+2.)/(8.+dot(p-c,p-c));
}

/*
// Original (607 chars):

#define n normalize
#define m(p) (length(mod(p,4.)-2.)-2.)

float t(vec3 p, inout vec3 d)
{
    float m,z = 8.;
    vec3 a,b,c = p;
    for(int i = 0; i++<999 && z<9.;)
    {
        a = sign(d);
        b = fract(-c*z*a);
        b += step(b,-b);
        a *= b/d;
        b = min(a.xxx,min(a.y,a.z));
        c += d*b/z;
        m = m(ceil(c*z+d*step(a,b))/z-.5/z)*z;
        z *= m<1.8?2.:1.;
    }
    d = c;
    return z;
}
void mainImage(out vec4 O, vec2 I)
{
    vec2 r = iResolution.xy,m=iMouse.xy,
    a = 3.*(m/r-.5)*sign(m);
    vec3 x = vec3(cos(a.x+vec2(0,11))*cos(a.y),sin(a.y)),
    y = n(vec3(-x.y,x.x,0)),
    z = n(cross(x,y)),
    
    d = n(mat3(x,y,z) * vec3(r.y,I+I-r)),
    p = d-d; p.x=iTime;
	float h = t(p,d),
    l = 9./(9.+dot(p-d,p-d));
    l *= mod(dot(ceil(d),d-d+1.),2.)+.4;
    O += l*m(d)*h/6.-O;
}
*/
/*
//528 chars:

#define V vec3
#define m(p) (length(mod(p,4.)-2.)-2.)
#define R mat2(cos(vec4(0,11,33,0)+a

V t(V p, V d)
{
    float z = 8.;
    V a,b,c = p;
    for(int i = 0; i++<999 && z<9.;)
    {
        a = sign(d);
        b = fract(-c*z*a);
        b += step(b,-b);
        a *= b/d;
        b = min(a.xxx,min(a.y,a.z));
        c += d*b/z;
        z *= m(ceil(c*z+d*step(a,b))/z-.5/z)*z<.8?2.:1.;
    }
    return c;
}
void mainImage(out vec4 O, vec2 I)
{
    V r = iResolution, m=iMouse.xyz,
    a = 3.*(m/r-.5)*sign(m),
    d = V(r.y,I+I-r.xy),
    p = d-d; p.x=iTime;
    d.xz *= R.y)); d.xy *= R.x));
	V v = t(p,normalize(d)),
    l = V(8)+dot(p-v,p-v);
    l = mod(dot(ceil(v),V(2))+1.,4.)/l;
    O.rgb = l+l*m(v)/.1;
}
*/

/*
//485 chars:

#define V vec3
#define m(p) (length(mod(p,4.)-2.)-2.)
#define R mat2(cos(vec4(0,11,33,0)+c

//void main(out vec4 O, vec2 I)
void main()
{
    V a = iResolution, b=V(iMouse),
    c = 3.*(b/a-.5)*sign(b),
    d = V(a.y,I+I-a.xy),
    p = V(iTime,0,0);
    d.xz *= R.y)); d.xy *= R.x));
    d /= length(d);
   
    c = p;
    float i=0.,z = 8.;
    for(;i++<1e3 && z<9.;)
    {
        a = sign(d);
        b = fract(-c*z*a);
        b += step(b,-b);
        a *= b/d;
        b = min(a.xxx,min(a.y,a.z));
        c += d*b/z;
        z *= m(ceil(c*z+d*step(a,b))/z-.5/z)*z<.8?2.:1.;
    }

    O.rgb = mod(dot(ceil(c),V(2))+1.,4.)/V(8.+dot(p-c,p-c))*(m(c)/z*1e2+1.);
}
*/