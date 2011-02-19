float4x4 world_matrix;
float4x4 view_proj_matrix;

struct VS_OUTPUT
{
   float4 Pos   : POSITION;
   float3 Norm  : TEXCOORD0;
   float2 Tex   : TEXCOORD4;
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
	//Out.Norm = normalize( mul( world_matrix, inNorm ) );
	Out.Norm = -normalize( mul( world_matrix, inNorm ) );
	
	// Propagate texture coordinate for the object:
	Out.Tex = inTex;
	
	return Out;
}




