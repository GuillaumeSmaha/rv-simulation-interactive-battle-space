// Composantes lumières (param_auto de Ogre)
float4 ambient;
float4 diffuse;
float4 specular;
float4 camPosition;
float4 lightPosition;

sampler baseMap;

float4 main( float4 Position: TEXCOORD0,
			 float3 Normal 	: TEXCOORD1,
             float2 Texcoord: TEXCOORD2 ) : COLOR
{
	// A sortir en variable accessible depuis Ogre ?
	float Ks = 0.28; // = 0.7 => brillance planète
	float Kd = 1.0;
	float Ka = 1.0;
	float n_specular = 6.0;
	
	float3 N = normalize(Normal);
	float3 EyeDir = normalize(camPosition - Position.xyz);
	float3 LightDir = normalize(lightPosition.xyz - (Position * lightPosition.w));
	float3 HalfAngle = normalize(LightDir + EyeDir);
	
	float N_L = dot(LightDir, N);
	float N_H = dot(HalfAngle, N);
	float4 Lit = lit(N_L, N_H, 200);

	// Compute ambient term:
	float4 AmbientColor = ambient * Ka;

	// Compute diffuse term:
	float4 DiffuseColor = Kd * diffuse * Lit.y;

	// Compute specular term:
	float4 SpecularColor = Ks * specular * Lit.z;
	
	float4 texColor = tex2D( baseMap, Texcoord);
   
	float4 FinalColor = (AmbientColor + DiffuseColor) * texColor + SpecularColor;
   
	return FinalColor;
}







