//~ uniform sampler2D baseMap;
//~ varying vec4 couleur;
//~ 
//~ 
//~ void main()
//~ {
	//~ vec4 color;
	//~ 
	//~ vec2 vectTex2 = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y);
	//~ 
	//~ color = texture2D( baseMap, vectTex2 );
	//~ 
	//~ color.a = 1.0 - couleur.a;
	//~ 
	//~ gl_FragColor = color;
//~ }


uniform sampler3D baseMap;
varying vec4 couleur;

void main()
{
	vec4 color;
	
	vec3 vectTex = vec3(gl_TexCoord[0].x, gl_TexCoord[0].y, 1.0 - couleur.a);
	
	color = texture3D( baseMap, vectTex );
	
	color.a = 1.0 - couleur.a;
	
	gl_FragColor = color;
}
