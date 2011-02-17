float4x4 world_matrix;
float4x4 view_proj_matrix;

struct VS_OUTPUT
{
   float4 Pos    : POSITION;
   float3 Norm   : TEXCOORD1;
   float2 Tex    : TEXCOORD2;
};

VS_OUTPUT main( 
   float4 inPos  : POSITION,
   float3 inNorm : NORMAL,
   float2 inTex  : TEXCOORD0 )
{
	VS_OUTPUT Out = (VS_OUTPUT) 0; 

	// Output transformed position:
	Out.Pos = mul( view_proj_matrix, inPos ); 

	// Transform the input normal to view space:
	Out.Norm = mul( world_matrix, inNorm );

	// Propagate texture coordinate for the object:
	Out.Tex = inTex;

	return Out;
}




