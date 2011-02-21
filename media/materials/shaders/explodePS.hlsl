
 
void main(
	float4 position	: POSITION,
	float2 uv		: TEXCOORD0,
	float4 color	: COLOR0,
 
	uniform sampler3D baseMap:register(s0),
 
	out float4 oColour	: COLOR)
{
	oColour = tex3D( baseMap, float3(uv.x, uv.y, 1.0 - color.a));
}
