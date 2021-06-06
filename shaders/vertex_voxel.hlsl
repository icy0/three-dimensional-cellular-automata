cbuffer per_frame : register(b0)
{
    float4x4 model_matrix;
    float4x4 view_matrix;
    float4x4 projection_matrix;
    int subdivision_level;
    float unused1;
    float unused2;
    float unused3;
}

struct vertexbuffer
{
    float3 position : POSITION0;
    float3 normal : NORMAL;
    float4 transformed_position : POSITION1;
};

struct vertex_shader_output
{
    float3 object_color : COLOR;
    nointerpolation float3 normal : NORMAL;
    float4 v_position : POSITION0;
    float4 position : SV_POSITION;
};

vertex_shader_output main(vertexbuffer vertex)
{
    vertex_shader_output output;

    float scale = 1 / pow(2, subdivision_level);

    float3 new_position = (scale * vertex.position) + vertex.transformed_position.xyz;
    float4x4 mvp = mul(model_matrix, mul(view_matrix, projection_matrix));

    output.normal = mul(float4(vertex.normal, 0.0f), model_matrix).xyz;
    output.v_position = mul(float4(new_position, 1.0f), model_matrix);
    
    float distance_to_center = length(output.v_position.xyz - float3(0.5f, -0.5f, -0.5f));
    output.object_color = float3((distance_to_center * 10) % 1.0f, (distance_to_center * 5) % 1.0f, 1.0f);

    output.position = mul(float4(new_position, 1.0f), mvp);

    return output;
}