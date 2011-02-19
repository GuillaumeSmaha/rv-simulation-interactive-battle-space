// Paramètres du shader param_auto de Ogre
float4 ambient;
float4 diffuse;
float4 specular;
float3 view_direction;
float3 light_direction;

sampler baseMap;

float4 main( float4 Diff	: COLOR0,
			 float3 Normal 	: TEXCOORD0,
             float2 Texcoord: TEXCOORD4 ) : COLOR
{
	// A sortir en variable accessible depuis Ogre ?
	float Ks = 0.28; // = 0.7 => brillance planète
	float Kd = 1.0;
	float Ka = 1.0;
	float n_specular = 6.0;
	
	float3 vReflect = normalize( (2.0 * Normal * dot( Normal, light_direction )) - light_direction );

	// Compute ambient term:
	float4 AmbientColor = ambient * Ka;

	// Compute diffuse term:
	float4 DiffuseColor = diffuse * Kd * max( 0, dot( Normal, light_direction ) );
	
	// Compute specular term:
	float4 SpecularColor = specular * Ks * pow( max( 0, dot( vReflect, view_direction ) ), n_specular );
	
	float4 texColor = tex2D( baseMap, Texcoord);
   
	float4 FinalColor = (AmbientColor + DiffuseColor) * texColor + SpecularColor;
   
	return FinalColor;
}







