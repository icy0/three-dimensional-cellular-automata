struct pixel_shader_input
{
    float4 color : COLOR;
    float3 normal : NORMAL;
    float4 position : SV_POSITION;
};
 
float4 main(pixel_shader_input input) : SV_TARGET
{
    float4 some_color = float4(0.1f, 0.1f, 0.1f, 1.0f);
    return some_color;
}