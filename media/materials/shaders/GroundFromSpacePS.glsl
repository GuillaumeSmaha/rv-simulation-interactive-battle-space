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

uniform sampler2D Texture0;
uniform vec4 ambient;
uniform vec4 diffuse;
uniform float fExposure;
uniform vec4 lightDirection;
uniform vec4 specular;
uniform vec4 viewDirection;

//
// Function declarations
//

vec4 ps_main( in vec4 Position, in vec4 fvRayleighColor, in vec4 fvMieColor, in vec2 Texcoord, in vec3 Normal );

//
// Function definitions
//

vec4 ps_main( in vec4 Position, in vec4 fvRayleighColor, in vec4 fvMieColor, in vec2 Texcoord, in vec3 Normal ) {
    float Ks = 0.280000;
    float Kd = 1.00000;
    float Ka = 1.00000;
    float n_specular = 6.00000;
    vec3 vReflect;
    vec4 AmbientColor;
    vec4 DiffuseColor;
    vec4 SpecularColor;
    vec4 texColor;
    vec4 atmoColor;

    vReflect = normalize( (((2.00000 * Normal) * dot( Normal, vec3( lightDirection))) - vec3( lightDirection)) );
    AmbientColor = (ambient * Ka);
    DiffuseColor = ((diffuse * Kd) * max( 0.000000, dot( Normal, vec3( lightDirection))));
    SpecularColor = ((specular * Ks) * pow( max( 0.000000, dot( vReflect, vec3( viewDirection))), n_specular));
    texColor = texture2D( Texture0, Texcoord);
    atmoColor = (1.00000 - exp( (( -fExposure ) * (((AmbientColor + DiffuseColor) * (fvRayleighColor + (texColor * fvMieColor))) + SpecularColor)) ));
    return atmoColor;
}


//
// Translator's entry point
//
void main() {
    vec4 xlat_retVal;

    xlat_retVal = ps_main( vec4(gl_TexCoord[0]), vec4(gl_TexCoord[1]), vec4(gl_TexCoord[2]), vec2(gl_TexCoord[3]), vec3(gl_TexCoord[4]));

    gl_FragData[0] = vec4( xlat_retVal);
}


 