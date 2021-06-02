cbuffer per_frame : register(b0)
{
    float4x4 model_matrix;
    float4x4 view_matrix;
    float4x4 projection_matrix;
}

struct vertexbuffer
{
    float3 position : POSITION0;
};

struct vertex_shader_output
{
    float4 position : SV_POSITION;
};

vertex_shader_output main(vertexbuffer vertex)
{
    vertex_shader_output output;

    float4x4 mvp = mul(model_matrix, mul(view_matrix, projection_matrix));

    output.position = mul(float4(vertex.position, 1.0f), mvp);

    return output;
}