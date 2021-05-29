cbuffer per_frame : register(b0)
{
    float4x4 model_matrix;
    float4x4 view_matrix;
    float4x4 projection_matrix;
}

struct vertexbuffer
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct vertex_shader_output
{
    float4 color : COLOR;
    float3 normal : NORMAL;
    float4 position : SV_POSITION;
};

vertex_shader_output main(vertexbuffer vertex)
{
    vertex_shader_output output;
    float4x4 mvp = mul(model_matrix, mul(view_matrix, projection_matrix));
    output.position = mul(float4(vertex.position, 1), mvp);
    output.color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    output.normal = vertex.normal;

    return output;
}