//
// Structure definitions
//

struct VS_OUTPUT {
    vec4 Pos;
    vec3 Norm;
    vec2 Tex;
};


//
// Global variable definitions
//

uniform mat4 view_proj_matrix;
uniform mat4 world_matrix;

//
// Function declarations
//

VS_OUTPUT xlat_main( in vec4 inPos, in vec3 inNorm, in vec2 inTex );

//
// Function definitions
//

VS_OUTPUT xlat_main( in vec4 inPos, in vec3 inNorm, in vec2 inTex ) {
    VS_OUTPUT Out;

    Out = VS_OUTPUT( vec4( 0.000000, 0.000000, 0.000000, 0.000000), vec3( 0.000000, 0.000000, 0.000000), vec2( 0.000000, 0.000000));
    Out.Pos = ( view_proj_matrix * inPos );
    Out.Norm = vec3( ( -normalize( ( world_matrix * vec4( inNorm, 0.000000) ) ) ));
    Out.Tex = inTex;
    return Out;
}


//
// Translator's entry point
//
void main() {
    VS_OUTPUT xlat_retVal;

    xlat_retVal = xlat_main( vec4(gl_Vertex), vec3(gl_Normal), vec2(gl_MultiTexCoord0));

    gl_Position = vec4( xlat_retVal.Pos);
    gl_TexCoord[0] = vec4( xlat_retVal.Norm, 0.0);
    gl_TexCoord[4] = vec4( xlat_retVal.Tex, 0.0, 0.0);
}


 