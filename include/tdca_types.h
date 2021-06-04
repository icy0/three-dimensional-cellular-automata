#pragma once

#include <directxmath.h>

#include "renderhub_types.h"

struct camera
{
    DirectX::XMFLOAT4X4 look_at;
    DirectX::XMFLOAT4X4 perspective;
};

struct lifespace_constant_buffer
{
    DirectX::XMFLOAT4X4 model;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMFLOAT4X4 projection;
};

struct voxel_constant_buffer
{
    DirectX::XMFLOAT4X4 model;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMFLOAT4X4 projection;
    int32 subdivision_level;
    real32 unused1;
    real32 unused2;
    real32 unused3;
};

struct voxel_instance_transforms
{
    DirectX::XMVECTOR translation;
};

struct lifespace_render_data
{
    ID3D11Buffer* constant_buffer;
    ID3D11Buffer* vertex_buffer;
    ID3D11Buffer* index_buffer;
    ID3D11VertexShader* vertex_shader;
    ID3D11PixelShader* pixel_shader;
    ID3D11InputLayout* input_layout;

    uint32 index_count;
    uint32 instance_count;
};

struct voxel_render_data
{
    ID3D11Buffer* constant_buffer;
    ID3D11Buffer* vertex_buffer;
    ID3D11Buffer* index_buffer;
    ID3D11Buffer* instance_buffer;
    ID3D11VertexShader* vertex_shader;
    ID3D11PixelShader* pixel_shader;
    ID3D11InputLayout* input_layout;

    uint32 index_count;
    uint32 instance_count;
};

struct dx_lifespace_vertex
{
    fvec3 position;
};

struct dx_voxel_vertex
{
    fvec3 position;
    fvec3 normal;
};

struct tdca_cell
{
    enum
    {
        DEAD = 0b0,
        ALIVE = 0b1
    };
    uint8 state;

    // decremented each frame. if 0, cell dies.
    uint8 lifetime;
};

struct tdca_lifespace
{
    uint32 subdivision_count;
    uint32 cell_count;

    tdca_cell* current_cells;
    tdca_cell* last_cells;
};

struct tdca_rule
{
    enum neighborhood
    {
        MOORE = 0b0,
        VON_NEUMANN = 0b1
    };
    uint8 neighborhood;
    uint8 necessary_amounts_of_alive_neighbors_for_surviving[26];
    uint8 necessary_amounts_of_alive_neighbors_for_birth[26];
    uint8 state_count;
};

// information structure about the spacial partitioning
// of our life space
struct tdca_spacial_partitioning_scheme
{
    enum scheme
    {
        BINARY = 0b0,
        OCTREE = 0b1
    };
    uint8 scheme;

    uint32 subdivision_count;
};

struct tdca
{
    tdca_rule rule;
    tdca_spacial_partitioning_scheme spacial_partitioning_scheme;
    tdca_lifespace lifespace;
};