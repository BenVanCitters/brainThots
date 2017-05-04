uniform vec3      iResolution;           //**xy viewport resolution (in pixels)
uniform float     iGlobalTime;           //* shader playback time (in seconds)
uniform float     renderDepth;           //number of steps to raymarch
uniform vec4      iMouse;                //xy mouse pixel coords. xy: current (if MLB down), zw: click
uniform float     blackout;              //blacking out the shader effect
uniform vec3      factor;
uniform vec4      tintColor; // tinting color
// The MIT License
// Copyright © 2013 Inigo Quilez
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
//software and associated documentation files (the "Software"), to deal in the Software
//without restriction, including without limitation the rights to use, copy, modify,
//merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
//persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or
//substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY
//OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


// A list of useful distance function to simple primitives, and an example on how to
// do some interesting boolean operations, repetition and displacement.
//
// More info here: http://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm


#define AA 0   // make this 1 is your machine is too slow

//------------------------------------------------------------------

float sdPlane( vec3 p )
{
    return p.y;
}

//position, size
float sdSphere( vec3 p, float s )
{
    return length(p)-s;
}

//------------------------------------------------------------------

float opS( float d1, float d2 )
{
    return max(-d2,d1);
}

vec2 opU( vec2 d1, vec2 d2 )
{
    return (d1.x<d2.x) ? d1 : d2;
}

vec3 opRep( vec3 p, vec3 c )
{
    return mod(p,c)-0.5*c;
}

// exponential smooth min (k = 32);
//float smin( float a, float b, float k )
//{
//    float res = exp( -k*a ) + exp( -k*b );
//    return -log( res )/k;
//}
// polynomial smooth min (k = 0.1);
float smin( float a, float b, float k )
{
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}
//------------------------------------------------------------------

vec2 map( in vec3 pos )
{
    vec3 pos1 = pos;
    pos1.x += iGlobalTime;
    pos1.z += iGlobalTime;
    
    vec3 pos2 = pos;
    pos2.x += iGlobalTime*.4;
    pos2.z += iGlobalTime*.1;
    
    vec3 pos3 = pos;
    pos3.x += iGlobalTime*1.3;
    pos3.z += iGlobalTime*.9;
    
    vec3 pos4 = pos;
    pos4.x -= iGlobalTime*0.4;
    pos4.z -= iGlobalTime*.5;
    
    float s1 = sdSphere( opRep(pos1,
                               vec3(1.1,0.0,1.1)) - vec3( 0.0,0.25, 0.0), 0.1 );
    float s2 = sdSphere( opRep(pos2,
                               vec3(1.4,0.0,1.7)) - vec3( 0.2,0.7, 0.2), 0.2 );
    float s3 = sdSphere( opRep(pos3,
                               vec3(1.8,0.0,1.4)) - vec3( 0.2,1.1, 0.2), 0.15 );
    float s4 = sdSphere( opRep(pos4,
                               vec3(6.7,0.0,4.1)) - vec3( 0.2,1.5, 0.2), 0.5 );
    float p1 = pos.y+0.01;//sdPlane(pos);
    
    float kSmooth = factor.x;
    vec2 res = vec2( smin(smin( s1,smin( s2,smin( s3,s4,kSmooth),kSmooth),kSmooth),p1,kSmooth),
                    46.9 ) ;
    //    vec2 res = opU( vec2( sdPlane(     pos), 1.0 ),
    //                   vec2( sdSphere(    opRep(pos,vec3(1.1,0.0,1.1))-vec3( 0.0,0.25, 0.0), 0.2 ), 46.9 ) );
    return res;
}

vec2 castRay( in vec3 ro, in vec3 rd )
{
    float tmin = 0.1;
    float tmax = 200.0;
    
#if 1
    // bounding volume
    float tp1 = (0.0-ro.y)/rd.y; if( tp1>0.0 ) tmax = min( tmax, tp1 );
    float tp2 = (1.6-ro.y)/rd.y; if( tp2>0.0 ) { if( ro.y>1.6 ) tmin = max( tmin, tp2 );
        else           tmax = min( tmax, tp2 ); }
#endif
    
    float t = tmin;
    float m = -1.0;
    for( int i=0; i<int(renderDepth); i++ )
    {
        float precis = 0.0005*t;
        vec2 res = map( ro+rd*t );
        if( res.x<precis || t>tmax ) break;
        t += res.x;
        m = res.y;
    }
    
    if( t>tmax ) m=-1.0;
    return vec2( t, m );
}


float softshadow( in vec3 ro, in vec3 rd, in float mint, in float tmax )
{
    float res = 1.5;
    float t = mint;
    for( int i=0; i<4; i++ )
    {
        float h = map( ro + rd*t ).x;
        res = min( res, 8.0*h/t );
        t += clamp( h, 0.02, 0.10 );
        if( h<0.0001 || t>tmax ) break;
    }
    return clamp( res, 0.0, 1.0 );
}

//surface normal?
vec3 calcNormal( in vec3 pos )
{
    vec2 e = vec2(1.0,-1.0)*0.5773*0.0005;
    return normalize( e.xyy*map( pos + e.xyy ).x +
                     e.yyx*map( pos + e.yyx ).x +
                     e.yxy*map( pos + e.yxy ).x +
                     e.xxx*map( pos + e.xxx ).x );
}

//ambient occulsion??
float calcAO( in vec3 pos, in vec3 nor )
{
    float occ = 0.0;
    float sca = 1.0;
    for( int i=0; i<5; i++ )
    {
        float hr = 0.01 + 0.12*float(i)/4.0;
        vec3 aopos =  nor * hr + pos;
        float dd = map( aopos ).x;
        occ += -(dd-hr)*sca;
        sca *= 0.95;
    }
    return clamp( 1.0 - 3.0*occ, 0.0, 1.0 );
}

//material rendering?
vec3 render( in vec3 ro, in vec3 rd )
{
    //sky color
    vec3 col = vec3(0.0, 0.0, 0.0);// +rd.y*0.8;
    vec2 res = castRay(ro,rd);
    float t = res.x;
    float m = res.y;
    if( m>-0.5 )
    {
        vec3 pos = ro + t*rd;
        vec3 nor = calcNormal( pos );
        vec3 ref = reflect( rd, nor );
        
        // material
        col = 0.45 + 0.35*sin( vec3(0.08,0.08,0.08)*(m-1.0) );
        //checkerboard pattern
        //if( m<1.5 )
        //{
        //    float f = mod( floor(5.0*pos.z) + floor(5.0*pos.x), 2.0);
        //    col = 0.3 + 0.1*f*vec3(1.0);
        //}
        
        // lighting
        //ambient occlusion
        float occ = calcAO( pos, nor );
        //directional light?
        vec3  lig = normalize( vec3(-0.4, 0.7, -0.6) );
        //ambient?
        float amb = clamp( 0.5+0.5*nor.y, 0.0, 1.0 );
        float dif = clamp( dot( nor, lig ), 0.0, 1.0 );
        float bac = clamp( dot( nor, normalize(vec3(-lig.x,0.0,-lig.z))), 0.0, 1.0 )*clamp( 1.0-pos.y,0.0,1.0);
        float dom = smoothstep( -0.1, 0.1, ref.y );
        float fre = pow( clamp(1.0+dot(nor,rd),0.0,1.0), 2.0 );
        //specular?
        float spe = pow(clamp( dot( ref, lig ), 0.0, 1.0 ),16.0);
        
        //dif *= softshadow( pos, lig, 0.02, 2.5 );
        //dom *= softshadow( pos, ref, 0.02, 2.5 );
        
        vec3 lin = vec3(0.0);
        lin += 1.30*dif*vec3(0.55,0.55,0.55);
        lin += 2.00*spe*vec3(0.90,0.90,0.90)*dif;
        lin += 0.40*amb*vec3(0.40,0.40,0.40)*occ;
        lin += 0.50*dom*vec3(0.60,0.60,0.60)*occ;
        lin += 0.50*bac*vec3(0.25,0.25,0.25)*occ;
        lin += 0.25*fre*vec3(1.00,1.00,1.00)*occ;
        col = col*lin;
        
        //fog color
        col = mix( col, vec3(0.0,0.0,0.0), 1.0-exp( -0.0002*t*t*t ) );
    }
    
    return vec3( clamp(col,0.0,1.0) );
}

mat3 setCamera( in vec3 ro, in vec3 ta, float cr )
{
    vec3 cw = normalize(ta-ro);
    vec3 cp = vec3(sin(cr), cos(cr),0.0);
    vec3 cu = normalize( cross(cw,cp) );
    vec3 cv = normalize( cross(cu,cw) );
    return mat3( cu, cv, cw );
}
//
void main()//Image( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 mo = iMouse.xy/iResolution.xy;
    mo.y = 1.0 - mo.y;
    float time = 15.0 + iGlobalTime;
    
    vec2 fragCoord = vec2(gl_TexCoord[0].x,iResolution.y-gl_TexCoord[0].y);
    
    vec3 tot = vec3(0.0);
#if AA>1
    for( int m=0; m<AA; m++ )
        for( int n=0; n<AA; n++ )
        {
            // pixel coordinates
            vec2 o = vec2(float(m),float(n)) / float(AA) - 0.5;
            vec2 p = (-iResolution.xy + 2.0*(fragCoord+o))/iResolution.y;
#else
            vec2 p = (-iResolution.xy + 2.0*fragCoord)/iResolution.y;
#endif
            
            // camera
            //look at vector?
            vec3 ro = vec3( -0.5+3.5*cos(0.5*time + 6.0*mo.x)+ time,
                           0.0 + 2.0*mo.y,
                           0.5 + 4.0*sin(0.5*time + 6.0*mo.x) );
            vec3 ta = vec3( -0.4+ time, -0.4, 0.5 );
            // camera-to-world transformation
            mat3 ca = setCamera( ro, ta, 0.0 );
            // ray direction
            vec3 rd = ca * normalize( vec3(p.xy,2.0) );
            
            // render
            vec3 col = render( ro, rd );
            
            // gamma
            col = pow( col, vec3(0.4545) );
            
            tot += col;
#if AA>1
        }
    tot /= float(AA*AA);
#endif
//    vec2 uv = fragCoord/ iResolution.xy;
//    gl_FragColor = vec4(uv*cos(iGlobalTime),0.0,1.0);
    
    gl_FragColor =tintColor* blackout*vec4( tot, 1.0 );//
}