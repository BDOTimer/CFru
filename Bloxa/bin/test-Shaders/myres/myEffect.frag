uniform sampler2D texture2;
uniform float     iTime;

void main()
{
    float a      = abs (sin (iTime / 10.0)) / 20.0 + 0.2;
    float factor = a / (0.001);
    vec2  pos    = floor(gl_TexCoord[0].xy * factor + 0.5) / factor;
    gl_FragColor = texture2D(texture2, pos);
}
