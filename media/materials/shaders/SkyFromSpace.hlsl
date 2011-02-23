float4x4 matWorldViewProjection;
float4 fvCameraPos;
float4 fvLightPos;
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
   float4 Position : POSITION0;      // Transformed vertex position
   float4 RayleighColor : TEXCOORD0;         // The Rayleigh color
   float4 MieColor : TEXCOORD1;         // The Mie color
   float3 Texcoord : TEXCOORD2;
};

struct VS_INPUT
{
	float4 Position : POSITION0;
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


   // Calculate the ray's start and end positions in the atmosphere, then calculate its scattering offset
   float fStartAngle = dot(fvRay, fvStart) / fOuterRadius;
   float fStartDepth = exp(-fInvScaleDepth);
   float fStartOffset = fStartDepth*scale(fStartAngle);


   float fSampleLength = fFar / fSamples;
   float fScaledLength = fSampleLength * fScale;
   float3 fvSampleRay = fvRay * fSampleLength;
   float3 fvSamplePoint = fvStart + fvSampleRay * 0.5;

   float4 lightDir = -fvLightDir;

   // Now loop through the sample rays
   float3 fvFrontColor = float3(0.0, 0.0, 0.0);
   for(int i=0; i<nSamples; i++)
   {
      float fHeight = length(fvSamplePoint);
      float fSampleDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
      float fLightAngle = dot(lightDir.xyz, fvSamplePoint) / fHeight;
      float fCameraAngle = dot(fvRay, fvSamplePoint) / fHeight;
      float fScatter = (fStartOffset + fSampleDepth *(scale(fLightAngle) - scale(fCameraAngle)));
      float3 fvAttenuate = exp(-fScatter * (fvInvWavelengths * fKr4PI + fKm4PI));
      fvFrontColor += fvAttenuate * (fSampleDepth * fScaledLength);
      fvSamplePoint += fvSampleRay;
   }


   Output.Position = mul(matWorldViewProjection, Input.Position);
   Output.RayleighColor = float4(fvFrontColor * (fvInvWavelengths * fKrESun),1.0);
   Output.MieColor = float4(fvFrontColor * fKmESun,1.0);
   Output.Texcoord = fvCameraPos.xyz - fvPos;

   return Output;
}

float fExposure;
#define fG  -0.990f
#define fG2  -0.990f * -0.990f

// Calculates the Mie phase function
float getMiePhase(float fCos, float fCos2, float g, float g2)
{
   return 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);
}

// Calculates the Rayleigh phase function
float getRayleighPhase(float fCos2)
{
   return 0.75 * (2.0 + 0.5 * fCos2);
   //return 0.75 + 0.75*fCos2;
}

float4 ps_main(float4 c0 : TEXCOORD0,
         float4 c1 : TEXCOORD1,
         float3 fvDirection : TEXCOORD2) : COLOR
{
	float4 lightDir = -fvLightDir;
	float fCos = dot(lightDir.xyz, fvDirection) / length(fvDirection);
	float fCos2 = fCos*fCos;
	float4 color = getRayleighPhase(fCos2) * c0 + getMiePhase(fCos, fCos2, fG, fG2) * c1;
	color.a = color.b;
	return 1 - exp(-fExposure * color);
}
