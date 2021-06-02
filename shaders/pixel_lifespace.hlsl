struct pixel_shader_input
{
    float4 position : SV_POSITION;
};
 
float4 main(pixel_shader_input input) : SV_TARGET
{
    return float4(0.0f, 1.0f, 0.0f, 1.0f);
}