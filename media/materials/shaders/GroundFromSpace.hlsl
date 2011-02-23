float4x4 matWorldViewProjection;
float4x4 worldMatrix;
float4 fvCameraPos;
float4 fvLightDir;

float3 fvInvWavelengths;
float fCameraHeightSqr;
float fInnerRadius;
float fOuterRadius;
float fOuterRadiusSqr;
float fKr4PI;
float fKm4PI;
float fKrESun;
float fKmESun;
float fScale;
float fScaleOverScaleDepth;




#define PI 3.14159f
#define nSamples 3
#define fSamples ((float)nSamples)

#define fInvScaleDepth (1.0f / 0.25)
#define fScaleDepth 0.25

// Returns the near intersection point of a line and a sphere
float getNearIntersection(float3 v3Pos, float3 v3Ray, float fDistance2, float fRadius2)
{
   float B = 2.0 * dot(v3Pos, v3Ray);
   float C = fDistance2 - fRadius2;
   float fDet = max(0.0, B*B - 4.0 * C);
   return 0.5 * (-B - sqrt(fDet));
}

// The scale equation calculated by Vernier's Graphical Analysis
float scale(float fCos)
{
   float x = 1.0 - fCos;
   return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

struct VS_OUTPUT
{
   float4 Position 		: POSITION0;      // Transformed vertex position
   float4 RayleighColor : TEXCOORD1;         // The Rayleigh color
   float4 MieColor 		: TEXCOORD2;         // The Mie color
   float2 Texcoord 		: TEXCOORD3;
   float3 Normal 		: TEXCOORD4;
};

struct VS_INPUT
{
	float4 Position : POSITION0;
	float3 Normal 	: NORMAL;
	float2 Texcoord : TEXCOORD0;
};


VS_OUTPUT vs_main(VS_INPUT Input)
{
   VS_OUTPUT Output;

   float3 fvPos = Input.Position.xyz;
   float3 fvRay = fvPos - fvCameraPos.xyz;

   fvPos = normalize(fvPos);
   float fFar = length(fvRay);
   fvRay /= fFar;

   

   // Calculate the closest intersection of the ray with the outer atmosphere (which is the near point of the ray passing through the atmosphere)
   float fNear = getNearIntersection(fvCameraPos, fvRay, fCameraHeightSqr, fOuterRadiusSqr);

   // Calculate the ray's starting position, then calculate its scattering offset
   float3 fvStart = fvCameraPos + fvRay * fNear;
   fFar -= fNear;
   float fDepth = exp((fInnerRadius - fOuterRadius) * fInvScaleDepth);
   float fCameraAngle = dot(-fvRay, fvPos) / fFar;
   float fLightAngle = dot(fvLightDir.xyz, fvPos) / fFar;
   float fCameraScale = scale(fCameraAngle);
   float fLightScale = scale(fLightAngle);
   float fCameraOffset = fDepth*fCameraScale;
   float fTemp = (fLightScale + fCameraScale);


   float fSampleLength = fFar / fSamples;
   float fScaledLength = fSampleLength * fScale;
   float3 fvSampleRay = fvRay * fSampleLength;
   float3 fvSamplePoint = fvStart + fvSampleRay * 0.5;

   // Now loop through the sample rays
   float3 fvFrontColor = float3(0.0, 0.0, 0.0);
   float3 fvAttenuate;
   for(int i=0; i<nSamples; i++)
   {
      float fHeight = length(fvSamplePoint);
      float fSampleDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
      float fScatter = fSampleDepth * fTemp - fCameraOffset;
      fvAttenuate = exp(-fScatter * (fvInvWavelengths * fKr4PI + fKm4PI));
      fvFrontColor += fvAttenuate * (fSampleDepth * fScaledLength);
      fvSamplePoint += fvSampleRay;
   }

   Output.Position = mul(matWorldViewProjection, Input.Position);
   Output.RayleighColor = float4(fvFrontColor * (fvInvWavelengths * fKrESun + fKmESun),1.0);
   Output.MieColor = float4(fvAttenuate, 1.0);
   Output.Texcoord = Input.Texcoord;
   Output.Normal = -normalize(mul( worldMatrix, Input.Normal ));
   
   return Output;
}

sampler2D Texture0;
float fExposure;
float4 ambient;
float4 diffuse;
float4 specular;
float4 viewDirection;
float4 lightDirection;

float4 ps_main(
		float4 Position			: TEXCOORD0,
		float4 fvRayleighColor 	: TEXCOORD1,
        float4 fvMieColor 		: TEXCOORD2,
        float2 Texcoord 		: TEXCOORD3,
		float3 Normal 			: TEXCOORD4
	) : COLOR
{
	// A sortir en variable accessible depuis Ogre ?
	float Ks = 0.28; // = 0.7 => brillance planète
	float Kd = 1.0;
	float Ka = 1.0;
	float n_specular = 6.0;
	
	float3 vReflect = normalize( (2.0 * Normal * dot( Normal, lightDirection )) - lightDirection );

	// Compute ambient term:
	float4 AmbientColor = ambient * Ka;

	// Compute diffuse term:
	float4 DiffuseColor = diffuse * Kd * max( 0, dot( Normal, lightDirection ) );

	// Compute specular term:
	float4 SpecularColor = specular * Ks * pow( max( 0, dot( vReflect, viewDirection ) ), n_specular );
	
	float4 texColor = tex2D( Texture0, Texcoord);
		
	return 1 - exp(-fExposure * ((AmbientColor + DiffuseColor) * (fvRayleighColor + texColor * fvMieColor) + SpecularColor));
	//return exp(-fExposure * (fvRayleighColor + texColor * fvMieColor));
	//return 1 - exp(-fExposure * (fvRayleighColor + texColor * fvMieColor));
}