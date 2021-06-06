#include <d3d11.h>
#include <directxmath.h>

#include "renderhub_types.h"
#include "renderhub_assert.h"
#include "win_renderhub_globals.h"
#include "win_renderhub_resourceloader.h"

#include "tdca_types.h"
#include "tdca_globals.h"

void init_lifespace_data()
{
    HRESULT result = -1;

    lifespace_constant_buffer vertex_shader_constant_buffer = {};
    vertex_shader_constant_buffer.view = g_camera->look_at;
    vertex_shader_constant_buffer.projection = g_camera->perspective;
    DirectX::XMStoreFloat4x4(&vertex_shader_constant_buffer.model, DirectX::XMMatrixIdentity());

    D3D11_BUFFER_DESC constant_buffer_description = {};
    constant_buffer_description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constant_buffer_description.ByteWidth = sizeof(lifespace_constant_buffer);
    constant_buffer_description.CPUAccessFlags = 0;
    constant_buffer_description.Usage = D3D11_USAGE_DEFAULT;
    constant_buffer_description.MiscFlags = 0;
    constant_buffer_description.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA constant_buffer_subres_data = {};
    constant_buffer_subres_data.pSysMem = &vertex_shader_constant_buffer;
    constant_buffer_subres_data.SysMemPitch = 0;
    constant_buffer_subres_data.SysMemSlicePitch = 0;

    rh_dx_logging(result = g_device->CreateBuffer(&constant_buffer_description, &constant_buffer_subres_data, &g_dx11_lifespace->constant_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_lifespace->constant_buffer)
    rh_dx_logging(g_device_context->VSSetConstantBuffers(0, 1, &g_dx11_lifespace->constant_buffer));

    dx_lifespace_vertex vertices[]
    {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, -1.0f, 0.0f},
        {0.0f, -1.0f, 0.0f},
        {0.0f, 0.0f, -1.0f},
        {1.0f, 0.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {0.0f, -1.0f, -1.0f}
    };

    uint32 indices[]
    {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        0, 4,
        1, 5,
        2, 6,
        3, 7,
        4, 5,
        5, 6,
        6, 7,
        7, 4
    };

    g_dx11_lifespace->index_count = ARRAYSIZE(indices);

    D3D11_BUFFER_DESC vertex_buffer_description = {};
    vertex_buffer_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_buffer_description.ByteWidth = sizeof(dx_lifespace_vertex) * ARRAYSIZE(vertices);
    vertex_buffer_description.CPUAccessFlags = 0;
    vertex_buffer_description.Usage = D3D11_USAGE_IMMUTABLE;
    vertex_buffer_description.MiscFlags = 0;
    vertex_buffer_description.StructureByteStride = sizeof(dx_lifespace_vertex);

    D3D11_SUBRESOURCE_DATA vertex_buffer_subres_data = {};
    vertex_buffer_subres_data.pSysMem = (void*) vertices;
    vertex_buffer_subres_data.SysMemPitch = 0;
    vertex_buffer_subres_data.SysMemSlicePitch = 0;

    result = -1;
    rh_dx_logging(result = g_device->CreateBuffer(&vertex_buffer_description, &vertex_buffer_subres_data, &g_dx11_lifespace->vertex_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_lifespace->vertex_buffer);

    uint32 stride = sizeof(dx_voxel_vertex);
    uint32 offset = 0;
    rh_dx_logging(g_device_context->IASetVertexBuffers(0, 1, &g_dx11_lifespace->vertex_buffer, &stride, &offset));

    D3D11_BUFFER_DESC index_buffer_description = {};
    index_buffer_description.BindFlags = D3D11_BIND_INDEX_BUFFER;
    index_buffer_description.ByteWidth = sizeof(uint32) * ARRAYSIZE(indices);
    index_buffer_description.CPUAccessFlags = 0;
    index_buffer_description.Usage = D3D11_USAGE_IMMUTABLE;
    index_buffer_description.MiscFlags = 0;
    index_buffer_description.StructureByteStride = sizeof(uint32);

    D3D11_SUBRESOURCE_DATA index_buffer_subres_data = {};
    index_buffer_subres_data.pSysMem = (void*) indices;
    index_buffer_subres_data.SysMemPitch = 0;
    index_buffer_subres_data.SysMemSlicePitch = 0;

    result = -1;
    rh_dx_logging(result = g_device->CreateBuffer(&index_buffer_description, &index_buffer_subres_data, &g_dx11_lifespace->index_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_lifespace->index_buffer);

    char* vertex_shader_bytes = nullptr;
    uint64 vertex_shader_size_in_bytes = 0;
    read_file_binary("vertex_shader_lifespace.cso", &vertex_shader_bytes, &vertex_shader_size_in_bytes);

    rh_dx_logging(g_device_context->IASetIndexBuffer(g_dx11_lifespace->index_buffer, DXGI_FORMAT_R32_UINT, 0));
    rh_dx_logging(g_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST));

    rh_dx_logging(result = g_device->CreateVertexShader((void*) vertex_shader_bytes, vertex_shader_size_in_bytes, nullptr, &g_dx11_lifespace->vertex_shader));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_lifespace->vertex_shader);

    D3D11_INPUT_ELEMENT_DESC input_layout_position = {};
    input_layout_position.SemanticName = "POSITION";
    input_layout_position.SemanticIndex = 0;
    input_layout_position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    input_layout_position.InputSlot = 0;
    input_layout_position.AlignedByteOffset = offsetof(dx_lifespace_vertex, position);
    input_layout_position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    input_layout_position.InstanceDataStepRate = 0;

    D3D11_INPUT_ELEMENT_DESC layouts[] {input_layout_position};

    rh_dx_logging(result = g_device->CreateInputLayout(layouts, ARRAYSIZE(layouts), (void*) vertex_shader_bytes, vertex_shader_size_in_bytes, &g_dx11_lifespace->input_layout));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_lifespace->input_layout);

    char* pixel_shader_bytes = nullptr;
    uint64 pixel_shader_size_in_bytes = 0;
    read_file_binary("pixel_shader_lifespace.cso", &pixel_shader_bytes, &pixel_shader_size_in_bytes);

    result = -1;
    rh_dx_logging(result = g_device->CreatePixelShader((void*) pixel_shader_bytes, pixel_shader_size_in_bytes, nullptr, &g_dx11_lifespace->pixel_shader));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_lifespace->pixel_shader);

    rh_dx_logging(g_device_context->IASetInputLayout(g_dx11_lifespace->input_layout));

    rh_dx_logging(g_device_context->VSSetShader(g_dx11_lifespace->vertex_shader, nullptr, 0));
    rh_dx_logging(g_device_context->PSSetShader(g_dx11_lifespace->pixel_shader, nullptr, 0));
}

void render_lifespace()
{
    lifespace_constant_buffer constant_buffer = {};
    DirectX::XMStoreFloat4x4(&constant_buffer.model, DirectX::XMMatrixIdentity());
    constant_buffer.projection = g_camera->perspective;
    constant_buffer.view = g_camera->look_at;

    g_device_context->UpdateSubresource(g_dx11_lifespace->constant_buffer, 0, nullptr, &constant_buffer, 0, 0);

    rh_dx_logging(g_device_context->VSSetConstantBuffers(0, 1, &g_dx11_lifespace->constant_buffer));

    uint32 stride = sizeof(dx_lifespace_vertex);
    uint32 offset = 0;
    rh_dx_logging(g_device_context->IASetVertexBuffers(0, 1, &g_dx11_lifespace->vertex_buffer, &stride, &offset));

    rh_dx_logging(g_device_context->IASetIndexBuffer(g_dx11_lifespace->index_buffer, DXGI_FORMAT_R32_UINT, 0));
    rh_dx_logging(g_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST));

    rh_dx_logging(g_device_context->IASetInputLayout(g_dx11_lifespace->input_layout));

    rh_dx_logging(g_device_context->VSSetShader(g_dx11_lifespace->vertex_shader, nullptr, 0));
    rh_dx_logging(g_device_context->PSSetShader(g_dx11_lifespace->pixel_shader, nullptr, 0));

    rh_dx_logging(g_device_context->DrawIndexed(g_dx11_lifespace->index_count, 0, 0));
}