/*
  Our explosion vertex program that just passes the alpha value of the vertex
  on to the fragment program
*/
void main(float4 position : POSITION,
			float2 uv		  : TEXCOORD0,
			float4 color	: COLOR0,
 
			out float4 oPosition : POSITION,
			out float2 oUv	   : TEXCOORD0,
			out float4 oColor   : COLOR0,
 
			uniform float4x4 worldViewProj)
{
	oPosition = mul(worldViewProj, position);
	oUv = uv;
	oColor = color;
}
