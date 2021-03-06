//
// Global variable definitions
//

uniform float fExposure;
uniform vec4 fvLightDir;

//
// Function declarations
//

float getRayleighPhase( in float fCos2 );
float getMiePhase( in float fCos, in float fCos2, in float g, in float g2 );
vec4 ps_main( in vec4 c0, in vec4 c1, in vec3 fvDirection );

//
// Function definitions
//

float getRayleighPhase( in float fCos2 ) {

    return (0.750000 * (2.00000 + (0.500000 * fCos2)));
}


float getMiePhase( in float fCos, in float fCos2, in float g, in float g2 ) {

    return (((1.50000 * ((1.00000 - g2) / (2.00000 + g2))) * (1.00000 + fCos2)) / pow( ((1.00000 + g2) - ((2.00000 * g) * fCos)), 1.50000));
}


vec4 ps_main( in vec4 c0, in vec4 c1, in vec3 fvDirection ) {
    float fCos;
    float fCos2;
    vec4 color;

	vec4 lightDir = -fvLightDir;
	
    fCos = (dot( lightDir.xyz , fvDirection) / length( fvDirection ));
    fCos2 = (fCos * fCos);
    color = ((getRayleighPhase( fCos2) * c0) + (getMiePhase( fCos, fCos2, -0.990000, 0.980100) * c1));
    color.w  = color.z ;
    return (1.00000 - exp( (( -fExposure ) * color) ));
}


//
// Translator's entry point
//
void main() {
    vec4 xlat_retVal;

    xlat_retVal = ps_main( vec4(gl_TexCoord[0]), vec4(gl_TexCoord[1]), vec3(gl_TexCoord[2]));

    gl_FragData[0] = vec4( xlat_retVal);
}


 