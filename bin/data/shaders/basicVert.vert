
//uniform sampler2D tex0;
//uniform vec2 uResolution;
//
//uniform float blurAmountShaderVar;
//uniform vec2 sampleOffset;


void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    vec4 eyeCoord  = gl_ModelViewMatrix * gl_Vertex;
    gl_Position    = gl_ProjectionMatrix * eyeCoord;
}
