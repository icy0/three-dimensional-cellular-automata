#pragma once

#include <directxmath.h>

#include "renderhub_types.h"

struct constant_buffer
{
    DirectX::XMFLOAT4X4 model;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMFLOAT4X4 projection;
    real32 scale_factor;
    real32 unused1;
    real32 unused2;
    real32 unused3;
};

struct dx_vertex
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