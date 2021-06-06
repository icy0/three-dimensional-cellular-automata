#include <d3d11.h>
#include <directxmath.h>

#include "renderhub_types.h"
#include "renderhub_assert.h"
#include "win_renderhub_globals.h"
#include "win_renderhub_resourceloader.h"

#include "tdca_types.h"
#include "tdca_globals.h"

DirectX::XMVECTOR calculate_cell_position_vector(tdca* tdca, cell_index cell)
{
    cell_index cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    cell_index cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);
    
    real32 x = ((real32) (cell % cells_per_axis)) / (real32) cells_per_axis;
    real32 y = -((real32) (((int32) ((real32) cell / cells_per_axis)) % (cells_per_slice / cells_per_axis)) / (real32) cells_per_axis);
    real32 z = -((real32) ((int32) ((real32) cell / cells_per_slice)) / (real32) cells_per_axis);

    return DirectX::XMVectorSet(x, y, z, 1.0f);
}

void update_voxels(tdca* tdca)
{
    cell_index alive_cells = 0;
    for(cell_index cell = 0; cell < tdca->lifespace.cell_count; cell++)
    {
        if(tdca->lifespace.current_cells[cell].state == tdca_cell::ALIVE || tdca->lifespace.current_cells[cell].state == tdca_cell::DYING)
        {
            alive_cells++;
        }
    }

    char buffer[256];
    snprintf(buffer, 256, "alive cells: %d/%d", alive_cells, tdca->lifespace.cell_count);
    rh_log_message(buffer);
    
    g_dx11_voxel->instance_count = alive_cells;

    // TODO this is too slow
    voxel_instance_transforms* instances = new voxel_instance_transforms[alive_cells];

    cell_index alive_cell_counter = 0;
    for(cell_index cell = 0; cell < tdca->lifespace.cell_count; cell++)
    {
        if(tdca->lifespace.current_cells[cell].state == tdca_cell::ALIVE || tdca->lifespace.current_cells[cell].state == tdca_cell::DYING)
        {
            instances[alive_cell_counter].translation = calculate_cell_position_vector(tdca, cell);
            alive_cell_counter++;
        }
    }

    D3D11_MAPPED_SUBRESOURCE instance_data = {};
    rh_dx_logging(g_device_context->Map(g_dx11_voxel->instance_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &instance_data));
    rh_assert(instance_data.pData);

    memcpy(instance_data.pData, instances, sizeof(voxel_instance_transforms) * alive_cells);

    rh_dx_logging(g_device_context->Unmap(g_dx11_voxel->instance_buffer, 0));

    delete[] instances;

    memcpy(tdca->lifespace.last_cells, tdca->lifespace.current_cells, sizeof(tdca_cell) * tdca->lifespace.cell_count);
    ZeroMemory(tdca->lifespace.current_cells, sizeof(tdca_cell) * tdca->lifespace.cell_count);
}

void init_voxel_data(tdca* tdca)
{
    HRESULT result = -1;

    g_dx11_voxel->constant_buffer_data = {};
    g_dx11_voxel->constant_buffer_data.view = g_camera->look_at;
    DirectX::XMStoreFloat4x4(&g_dx11_voxel->constant_buffer_data.model, DirectX::XMMatrixIdentity());

    DirectX::XMStoreFloat4x4(&g_dx11_voxel->constant_buffer_data.projection, 
        DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(70.0f), 16.0f/9.0f, 0.1f, 1000.0f));

    g_dx11_voxel->constant_buffer_data.subdivision_level = tdca->lifespace.subdivision_count;

    dx_voxel_vertex vertices[]
    {
    //   {pos},      {normal}           {pos},        {normal}          {pos},        {normal}          {pos},        {normal}
        {{0, 0, 0},  {0, 0, 1}},        {{1, 0, 0},   {0, 0, 1}},       {{0, -1, 0},  {0, 0, 1}},       {{1, -1, 0},  {0, 0, 1}},   // front face
        {{1, 0, 0},  {1, 0, 0}},        {{1, 0, -1},  {1, 0, 0}},       {{1, -1, 0},  {1, 0, 0}},       {{1, -1, -1}, {1, 0, 0}},   // right face
        {{1, 0, -1}, {0, 0, -1}},       {{0, 0, -1},  {0, 0, -1}},      {{1, -1, -1}, {0, 0, -1}},      {{0, -1, -1}, {0, 0, -1}},  // back face
        {{0, 0, -1}, {-1, 0, 0}},       {{0, 0, 0},   {-1, 0, 0}},      {{0, -1, -1}, {-1, 0, 0}},      {{0, -1, 0},  {-1, 0, 0}},  // left face
        {{1, 0, -1}, {0, 1, 0}},        {{1, 0, 0},   {0, 1, 0}},       {{0, 0, -1},  {0, 1, 0}},       {{0, 0, 0},   {0, 1, 0}},   // top face
        {{1, -1, 0}, {0, -1, 0}},       {{1, -1, -1}, {0, -1, 0}},      {{0, -1, 0},  {0, -1, 0}},      {{0, -1, -1}, {0, -1, 0}}   // bottom face
    };

    voxel_instance_transforms* instances = new voxel_instance_transforms[tdca->lifespace.cell_count];
    ZeroMemory(instances, sizeof(instances));

    g_dx11_voxel->instance_count = 0;

    uint32 indices[]
    {
        0, 1, 2,
        1, 3, 2,
        4, 5, 6,
        5, 7, 6,
        8, 9, 10,
        9, 11, 10,
        12, 13, 14,
        13, 15, 14,
        16, 17, 18,
        17, 19, 18,
        20, 21, 22,
        21, 23, 22
    };

    g_dx11_voxel->index_count = ARRAYSIZE(indices);

    D3D11_BUFFER_DESC constant_buffer_description = {};
    constant_buffer_description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constant_buffer_description.ByteWidth = sizeof(voxel_constant_buffer);
    constant_buffer_description.CPUAccessFlags = 0;
    constant_buffer_description.Usage = D3D11_USAGE_DEFAULT;
    constant_buffer_description.MiscFlags = 0;
    constant_buffer_description.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA constant_buffer_subres_data = {};
    constant_buffer_subres_data.pSysMem = &g_dx11_voxel->constant_buffer_data;
    constant_buffer_subres_data.SysMemPitch = 0;
    constant_buffer_subres_data.SysMemSlicePitch = 0;

    rh_dx_logging(result = g_device->CreateBuffer(&constant_buffer_description, &constant_buffer_subres_data, &g_dx11_voxel->constant_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_voxel->constant_buffer)
    rh_dx_logging(g_device_context->VSSetConstantBuffers(0, 1, &g_dx11_voxel->constant_buffer));

    D3D11_BUFFER_DESC vertex_buffer_description = {};
    vertex_buffer_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_buffer_description.ByteWidth = sizeof(dx_voxel_vertex) * ARRAYSIZE(vertices);
    vertex_buffer_description.CPUAccessFlags = 0;
    vertex_buffer_description.Usage = D3D11_USAGE_IMMUTABLE;
    vertex_buffer_description.MiscFlags = 0;
    vertex_buffer_description.StructureByteStride = sizeof(dx_voxel_vertex);

    D3D11_SUBRESOURCE_DATA vertex_buffer_subres_data = {};
    vertex_buffer_subres_data.pSysMem = (void*) vertices;
    vertex_buffer_subres_data.SysMemPitch = 0;
    vertex_buffer_subres_data.SysMemSlicePitch = 0;

    result = -1;
    rh_dx_logging(result = g_device->CreateBuffer(&vertex_buffer_description, &vertex_buffer_subres_data, &g_dx11_voxel->vertex_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_voxel->vertex_buffer);

    uint32 stride = sizeof(dx_voxel_vertex);
    uint32 offset = 0;
    rh_dx_logging(g_device_context->IASetVertexBuffers(0, 1, &g_dx11_voxel->vertex_buffer, &stride, &offset));

    D3D11_BUFFER_DESC instance_buffer_description = {};
    instance_buffer_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    instance_buffer_description.ByteWidth = sizeof(voxel_instance_transforms) * tdca->lifespace.cell_count;
    instance_buffer_description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    instance_buffer_description.Usage = D3D11_USAGE_DYNAMIC;
    instance_buffer_description.MiscFlags = 0;
    instance_buffer_description.StructureByteStride = sizeof(voxel_instance_transforms);

    D3D11_SUBRESOURCE_DATA instance_buffer_subres_data = {};
    instance_buffer_subres_data.pSysMem = (void*) instances;
    instance_buffer_subres_data.SysMemPitch = 0;
    instance_buffer_subres_data.SysMemSlicePitch = 0;

    result = -1;
    rh_dx_logging(result = g_device->CreateBuffer(&instance_buffer_description, &instance_buffer_subres_data, &g_dx11_voxel->instance_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_voxel->instance_buffer);

    delete[] instances;

    stride = sizeof(voxel_instance_transforms);
    offset = 0;
    rh_dx_logging(g_device_context->IASetVertexBuffers(1, 1, &g_dx11_voxel->instance_buffer, &stride, &offset));

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
    rh_dx_logging(result = g_device->CreateBuffer(&index_buffer_description, &index_buffer_subres_data, &g_dx11_voxel->index_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_voxel->index_buffer);

    char* vertex_shader_bytes = nullptr;
    uint64 vertex_shader_size_in_bytes = 0;
    read_file_binary("vertex_shader_voxel.cso", &vertex_shader_bytes, &vertex_shader_size_in_bytes);

    rh_dx_logging(g_device_context->IASetIndexBuffer(g_dx11_voxel->index_buffer, DXGI_FORMAT_R32_UINT, 0));
    rh_dx_logging(g_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

    rh_dx_logging(result = g_device->CreateVertexShader((void*) vertex_shader_bytes, vertex_shader_size_in_bytes, nullptr, &g_dx11_voxel->vertex_shader));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_voxel->vertex_shader);

    D3D11_INPUT_ELEMENT_DESC input_layout_position = {};
    input_layout_position.SemanticName = "POSITION";
    input_layout_position.SemanticIndex = 0;
    input_layout_position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    input_layout_position.InputSlot = 0;
    input_layout_position.AlignedByteOffset = offsetof(dx_voxel_vertex, position);
    input_layout_position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    input_layout_position.InstanceDataStepRate = 0;
    
    D3D11_INPUT_ELEMENT_DESC input_layout_normal = {};
    input_layout_normal.SemanticName = "NORMAL";
    input_layout_normal.SemanticIndex = 0;
    input_layout_normal.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    input_layout_normal.InputSlot = 0;
    input_layout_normal.AlignedByteOffset = offsetof(dx_voxel_vertex, normal);
    input_layout_normal.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    input_layout_normal.InstanceDataStepRate = 0;
    
    D3D11_INPUT_ELEMENT_DESC input_layout_instance_position = {};
    input_layout_instance_position.SemanticName = "POSITION";
    input_layout_instance_position.SemanticIndex = 1;
    input_layout_instance_position.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    input_layout_instance_position.InputSlot = 1;
    input_layout_instance_position.AlignedByteOffset = 0;
    input_layout_instance_position.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
    input_layout_instance_position.InstanceDataStepRate = 1;

    D3D11_INPUT_ELEMENT_DESC layouts[] {input_layout_position, input_layout_normal, input_layout_instance_position};

    rh_dx_logging(result = g_device->CreateInputLayout(layouts, ARRAYSIZE(layouts), (void*) vertex_shader_bytes, vertex_shader_size_in_bytes, &g_dx11_voxel->input_layout));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_voxel->input_layout);

    char* pixel_shader_bytes = nullptr;
    uint64 pixel_shader_size_in_bytes = 0;
    read_file_binary("pixel_shader_voxel.cso", &pixel_shader_bytes, &pixel_shader_size_in_bytes);

    result = -1;
    rh_dx_logging(result = g_device->CreatePixelShader((void*) pixel_shader_bytes, pixel_shader_size_in_bytes, nullptr, &g_dx11_voxel->pixel_shader));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_dx11_voxel->pixel_shader);

    rh_dx_logging(g_device_context->IASetInputLayout(g_dx11_voxel->input_layout));

    rh_dx_logging(g_device_context->VSSetShader(g_dx11_voxel->vertex_shader, nullptr, 0));
    rh_dx_logging(g_device_context->PSSetShader(g_dx11_voxel->pixel_shader, nullptr, 0));
}

void render_voxels(tdca* tdca)
{
    DirectX::XMStoreFloat4x4(&g_dx11_voxel->constant_buffer_data.model, DirectX::XMMatrixIdentity());
    g_dx11_voxel->constant_buffer_data.projection = g_camera->perspective;
    g_dx11_voxel->constant_buffer_data.view = g_camera->look_at;

    g_device_context->UpdateSubresource(g_dx11_voxel->constant_buffer, 0, nullptr, &g_dx11_voxel->constant_buffer_data, 0, 0);
    rh_dx_logging(g_device_context->VSSetConstantBuffers(0, 1, &g_dx11_voxel->constant_buffer));

    uint32 stride = sizeof(dx_voxel_vertex);
    uint32 offset = 0;
    rh_dx_logging(g_device_context->IASetVertexBuffers(0, 1, &g_dx11_voxel->vertex_buffer, &stride, &offset));

    stride = sizeof(voxel_instance_transforms);
    offset = 0;
    rh_dx_logging(g_device_context->IASetVertexBuffers(1, 1, &g_dx11_voxel->instance_buffer, &stride, &offset));

    rh_dx_logging(g_device_context->IASetIndexBuffer(g_dx11_voxel->index_buffer, DXGI_FORMAT_R32_UINT, 0));
    rh_dx_logging(g_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

    rh_dx_logging(g_device_context->IASetInputLayout(g_dx11_voxel->input_layout));

    rh_dx_logging(g_device_context->VSSetShader(g_dx11_voxel->vertex_shader, nullptr, 0));
    rh_dx_logging(g_device_context->PSSetShader(g_dx11_voxel->pixel_shader, nullptr, 0));

    rh_dx_logging(g_device_context->DrawIndexedInstanced(g_dx11_voxel->index_count, g_dx11_voxel->instance_count, 0, 0, 0));
}