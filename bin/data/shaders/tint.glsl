// Uniforms
uniform sampler2DRect tex0;
uniform vec2 uResolution;
uniform vec4 tintColor;

//returns a grey for a given hue
vec4 getDesaturatedGrey(vec4 color)
{
    float level =(color.r * 0.299) + (color.g * 0.587) + (color.b * 0.144);
    return vec4(level,level,level,color.a);
}

void main()
{
    vec2 position = uResolution * gl_TexCoord[0].st;
    gl_FragColor = tintColor*getDesaturatedGrey(texture2DRect( tex0, gl_TexCoord[0].st ));
}


