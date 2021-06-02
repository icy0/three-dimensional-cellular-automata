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

struct cell
{
    enum
    {
        ALIVE = 0b1,
        DEAD = 0b01
    };
    uint8 state;

    // decremented each frame. if 0, cell dies.
    uint32 lifetime;

    // lifetime on birth.
    uint32 max_lifetime;
};

struct life_space
{
    // number of cells is then equal to 2 ^ subdivision_count
    uint32 subdivision_count;

    cell* cells;
};

// information structure about the spacial partitioning
// of our life space
struct spacial_partitioning_scheme
{
    enum
    {
        OCTREE = 0b1,
        // for future extensions
    };
    uint8 scheme;

    uint32 subdivision_count;
};