// Uniforms
uniform sampler2DRect tex0;
uniform vec2 uResolution;

uniform float blurAmountShaderVar;
uniform vec2 sampleOffset;

uniform float time;
uniform float factor1;
uniform float factor2;
uniform float factor3;
uniform float factor4;
uniform float blackout;
float weights[21];

void main()
{
    float weightCount = 10.0;
    weights[0] = 0.0091679276560113852;
    weights[1] = 0.014053461291849008;
    weights[2] = 0.020595286319257878;
    weights[3] = 0.028855245532226279;
    weights[4] = 0.038650411513543079;
    weights[5] = 0.049494378859311142;
    weights[6] = 0.060594058578763078;
    weights[7] = 0.070921288047096992;
    weights[8] = 0.079358891804948081;
    weights[9] = 0.084895951965930902;
    weights[10] = 0.086826196862124602;
    weights[11] = 0.084895951965930902;
    weights[12] = 0.079358891804948081;
    weights[13] = 0.070921288047096992;
    weights[14] = 0.060594058578763092;
    weights[15] = 0.049494378859311121;
    weights[16] = 0.0386504115135431;
    weights[17] = 0.028855245532226279;
    weights[18] = 0.020595286319257885;
    weights[19] = 0.014053461291849008;
    weights[20] = 0.00916792765601138;

    vec2 sampleOffset = vec2(blurAmountShaderVar,blurAmountShaderVar);
    sampleOffset *= .1; //~~ /= weightCount;

    vec2 position = uResolution * gl_TexCoord[0].st;
    vec2 inputOffset = factor1* vec2(cos(time + position.x*factor1 * 0.125 ),
                                     sin(time*0.91 + position.x *0.33 + position.y /(0.001+factor2*9.0)));
    inputOffset += factor3* vec2(cos(5.0 +time + position.y * 0.0763),
                                 sin(9.0 +time * 0.6 + position.y * 0.04 ));
    
    inputOffset += factor4* vec2(factor4*cos(12.0 + time * 1.7 + position.y * 0.13),
                                 sin(7.0 +time * 0.6 + position.x * 0.030 ));
    position = position + inputOffset;

    vec4 sum = vec4( 0.0, 0.0, 0.0 , 0.0);
    vec2 baseOffset = -weightCount * sampleOffset;

    vec2 offset = vec2( 0.0, 0.0 );
    for( int s = 0; s < 21; ++s )
    {
        vec2 texcord = position.st + vec2(baseOffset.x + offset.x, 0.0);
        sum += texture2DRect( tex0, texcord ) * weights[s];
        offset.x += sampleOffset.x;
    }

    gl_FragColor = sum*vec4(blackout,blackout,blackout,1);// vec4(vTexCoord.x,vTexCoord.y,0.0,1.0);//vec4(gl_TexCoord[0].x,gl_TexCoord[0].y,0.0,1.0);//texture2DRect( tex0, uResolution*gl_TexCoord[0].st );//
}
