struct pixel_shader_input
{
    float3 object_color : COLOR;
    nointerpolation float3 normal : NORMAL;
    float4 v_position : POSITION0;
};
 
float4 main(pixel_shader_input input) : SV_TARGET
{
    float3 object_color = float3(1.0f, 1.0f, 1.0f); // white
    float3 light_color = float3(0.8f, 0.5f, 0.2f); // bright yellow
    // float3 light_color = float3(1.0f, 1.0f, 1.0f);

    float3 camera_pos = float3(0.5f, -0.5f, 3.0f);
    float3 light_position = float3(1.5f, -0.5f, 3.0f);
    float3 normal = input.normal;
    float ambient_strength = 0.1f;
    float specular_strength = 0.2f;

    float3 ambient_color = ambient_strength * light_color;

    float3 camera_direction = normalize(input.v_position.xyz - camera_pos);
    float3 light_direction = normalize(light_position - input.v_position.xyz);

    float diffuse_impact_of_light = max(dot(normal, light_direction), 0.0f);
    float3 diffuse_color = mul(diffuse_impact_of_light, light_color);

    float3 reflection_direction = reflect(light_direction, normal);
    float specular_impact = pow(max(dot(camera_direction, reflection_direction), 0.0), 8);
    float3 specular_color = specular_strength * specular_impact * light_color;

    // float4 output_color = float4((ambient_color + diffuse_color /*+ specular_color*/) * input.object_color, 1.0f);
    float4 output_color = float4((ambient_color + diffuse_color /*+ specular_color*/) * object_color, 1.0f);
    return output_color;
}