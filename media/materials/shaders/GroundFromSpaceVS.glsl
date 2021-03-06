//
// Structure definitions
//

struct VS_OUTPUT {
    vec4 Position;
    vec4 RayleighColor;
    vec4 MieColor;
    vec2 Texcoord;
    vec3 Normal;
};

struct VS_INPUT {
    vec4 Position;
    vec3 Normal;
    vec2 Texcoord;
};


//
// Global variable definitions
//

uniform float fCameraHeightSqr;
uniform float fInnerRadius;
uniform float fKm4PI;
uniform float fKmESun;
uniform float fKr4PI;
uniform float fKrESun;
uniform float fOuterRadius;
uniform float fOuterRadiusSqr;
uniform float fScale;
uniform float fScaleOverScaleDepth;
uniform vec4 fvCameraPos;
uniform vec3 fvInvWavelengths;
uniform vec4 fvLightPos;
uniform mat4 matWorldViewProjection;
uniform mat4 worldMatrix;

//
// Function declarations
//

float getNearIntersection( in vec3 v3Pos, in vec3 v3Ray, in float fDistance2, in float fRadius2 );
float scale( in float fCos );
VS_OUTPUT vs_main( in VS_INPUT Input );

//
// Function definitions
//

float getNearIntersection( in vec3 v3Pos, in vec3 v3Ray, in float fDistance2, in float fRadius2 ) {
    float B;
    float C;
    float fDet;

    B = (2.00000 * dot( v3Pos, v3Ray));
    C = (fDistance2 - fRadius2);
    fDet = max( 0.000000, ((B * B) - (4.00000 * C)));
    return (0.500000 * (( -B ) - sqrt( fDet )));
}


float scale( in float fCos ) {
    float x;

    x = (1.00000 - fCos);
    return (0.250000 * exp( (-0.00287000 + (x * (0.459000 + (x * (3.83000 + (x * (-6.80000 + (x * 5.25000)))))))) ));
}


VS_OUTPUT vs_main( in VS_INPUT Input ) {
    vec3 fvPos;
    vec3 fvRay;
    float fFar;
    float fNear;
    vec3 fvStart;
    float fDepth;
    float fCameraAngle;
    float fLightAngle;
    float fCameraScale;
    float fLightScale;
    float fCameraOffset;
    float fTemp;
    float fSampleLength;
    float fScaledLength;
    vec3 fvSampleRay;
    vec3 fvSamplePoint;
    vec3 fvFrontColor = vec3( 0.000000, 0.000000, 0.000000);
    int i = 0;
    float fHeight;
    float fSampleDepth;
    float fScatter;
    vec3 fvAttenuate;
    VS_OUTPUT Output;

    fvPos = Input.Position.xyz ;
    fvRay = (fvPos - fvCameraPos.xyz );
    fvPos = normalize( fvPos );
    fFar = length( fvRay );
    fvRay /= fFar;
    fNear = getNearIntersection( vec3( fvCameraPos), fvRay, fCameraHeightSqr, fOuterRadiusSqr);
    fvStart = (vec3( fvCameraPos) + (fvRay * fNear));
    fFar -= fNear;
    fDepth = exp( ((fInnerRadius - fOuterRadius) * 4.00000) );
    fCameraAngle = (dot( ( -fvRay ), fvPos) / fFar);
    fLightAngle = (dot( fvLightPos.xyz , fvPos) / fFar);
    fCameraScale = scale( fCameraAngle);
    fLightScale = scale( fLightAngle);
    fCameraOffset = (fDepth * fCameraScale);
    fTemp = (fLightScale + fCameraScale);
    fSampleLength = (fFar / 3.00000);
    fScaledLength = (fSampleLength * fScale);
    fvSampleRay = (fvRay * fSampleLength);
    fvSamplePoint = (fvStart + (fvSampleRay * 0.500000));
    for ( ; (i < 3); ( i++ )) {
        fHeight = length( fvSamplePoint );
        fSampleDepth = exp( (fScaleOverScaleDepth * (fInnerRadius - fHeight)) );
        fScatter = ((fSampleDepth * fTemp) - fCameraOffset);
        fvAttenuate = exp( (( -fScatter ) * ((fvInvWavelengths * fKr4PI) + fKm4PI)) );
        fvFrontColor += (fvAttenuate * (fSampleDepth * fScaledLength));
        fvSamplePoint += fvSampleRay;
    }
    Output.Position = ( matWorldViewProjection * Input.Position );
    Output.RayleighColor = vec4( (fvFrontColor * ((fvInvWavelengths * fKrESun) + fKmESun)), 1.00000);
    Output.MieColor = vec4( fvAttenuate, 1.00000);
    Output.Texcoord = Input.Texcoord;
    Output.Normal = vec3( ( -normalize( ( worldMatrix * vec4( Input.Normal, 0.000000) ) ) ));
    return Output;
}


//
// Translator's entry point
//
void main() {
    VS_OUTPUT xlat_retVal;
    VS_INPUT xlat_temp_Input;
    xlat_temp_Input.Position = vec4( gl_Vertex);
    xlat_temp_Input.Normal = vec3( gl_Normal);
    xlat_temp_Input.Texcoord = vec2( gl_MultiTexCoord0);

    xlat_retVal = vs_main( xlat_temp_Input);

    gl_Position = vec4( xlat_retVal.Position);
    gl_TexCoord[1] = vec4( xlat_retVal.RayleighColor);
    gl_TexCoord[2] = vec4( xlat_retVal.MieColor);
    gl_TexCoord[3] = vec4( xlat_retVal.Texcoord, 0.0, 0.0);
    gl_TexCoord[4] = vec4( xlat_retVal.Normal, 0.0);
}


 