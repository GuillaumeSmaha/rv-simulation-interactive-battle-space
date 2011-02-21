//
// Structure definitions
//

varying vec4 couleur;


//
// Translator's entry point
//
void main() {	
    gl_Position = ftransform();
    couleur = gl_Color;
    
    gl_TexCoord[0] = vec4(gl_MultiTexCoord0.xy, 0.0, 0.0);
}

