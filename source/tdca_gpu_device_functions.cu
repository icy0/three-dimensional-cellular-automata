#include <cstdio>
#include <cstdlib>

#include "tdca_types.h"
#include "tdca_globals.h"

#include <cuda_runtime_api.h>
#include <cuda_d3d11_interop.h>

cudaGraphicsResource* g_graphics_resource;

voxel_instance_transforms* g_instances;

__device__ unsigned int cell_state(tdca* tdca, cell_index cell)
{
    if(cell < 0 || cell > tdca->lifespace.cell_count)
    {
        return 0;
    }
    else
    {
        return tdca->lifespace.last_cells[cell].state;
    }
}

__device__ bool is_in_bounds_relative(tdca* tdca, cell_index origin, cell_index target)
{
    int cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    int cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    // the row of cells the current cell index resides in
    cell_index row_start_cell_inclusive = origin - (origin % cells_per_axis);
    cell_index row_end_cell_inclusive = row_start_cell_inclusive + cells_per_axis - 1;

    // the vertical slice of cells the current cell resides in
    cell_index slice_start_cell_inclusive = origin - (origin % cells_per_slice);
    cell_index slice_end_cell_inclusive = slice_start_cell_inclusive + cells_per_slice - 1;

    int difference =  target - origin;

    bool cell_is_right =   difference == 1 
                            || difference == -cells_per_axis + 1 
                            || difference == cells_per_axis + 1 
                            || difference == - cells_per_slice + 1 
                            || difference == - cells_per_slice + -cells_per_axis + 1 
                            || difference == - cells_per_slice + cells_per_axis + 1 
                            || difference == + cells_per_slice + 1 
                            || difference == + cells_per_slice + -cells_per_axis + 1 
                            || difference == + cells_per_slice + cells_per_axis + 1;
    
    bool cell_is_left =    difference == -1 
                            || difference == -cells_per_axis - 1 
                            || difference == cells_per_axis - 1 
                            || difference == - cells_per_slice - 1 
                            || difference == - cells_per_slice + -cells_per_axis - 1 
                            || difference == - cells_per_slice + cells_per_axis - 1 
                            || difference == + cells_per_slice - 1 
                            || difference == + cells_per_slice + -cells_per_axis - 1 
                            || difference == + cells_per_slice + cells_per_axis - 1;

    bool cell_is_top =     difference == -cells_per_axis
                            || difference == -cells_per_axis - 1
                            || difference == -cells_per_axis + 1
                            || difference == -cells_per_axis - cells_per_slice
                            || difference == -cells_per_axis - cells_per_slice - 1
                            || difference == -cells_per_axis - cells_per_slice + 1
                            || difference == -cells_per_axis +  cells_per_slice
                            || difference == -cells_per_axis +  cells_per_slice - 1
                            || difference == -cells_per_axis +  cells_per_slice + 1;

    bool cell_is_bottom =  difference == cells_per_axis
                            || difference == cells_per_axis - 1
                            || difference == cells_per_axis + 1
                            || difference == cells_per_axis - cells_per_slice
                            || difference == cells_per_axis - cells_per_slice - 1
                            || difference == cells_per_axis - cells_per_slice + 1
                            || difference == cells_per_axis +  cells_per_slice
                            || difference == cells_per_axis +  cells_per_slice - 1
                            || difference == cells_per_axis +  cells_per_slice + 1;

    if(cell_is_right)
        if ((origin + 1) > row_end_cell_inclusive) return false;
    if(cell_is_left)
        if ((origin - 1) < row_start_cell_inclusive) return false;
    if(cell_is_top)
        if ((origin - cells_per_axis) < slice_start_cell_inclusive) return false;
    if(cell_is_bottom)
        if ((origin + cells_per_axis) > slice_end_cell_inclusive) return false;

    return true;
}

__device__ void count_alive_neighbors_moore(tdca* tdca, cell_index cell, unsigned int* alive_neighbors_count)
{
    int cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    int cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    if(is_in_bounds_relative(tdca, cell, cell - 1))                                       *alive_neighbors_count += (cell_state(tdca, cell - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + 1))                                       *alive_neighbors_count += (cell_state(tdca, cell + 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_axis))                          *alive_neighbors_count += (cell_state(tdca, cell - cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_axis - 1))                      *alive_neighbors_count += (cell_state(tdca, cell - cells_per_axis - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_axis + 1))                      *alive_neighbors_count += (cell_state(tdca, cell - cells_per_axis + 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_axis))                          *alive_neighbors_count += (cell_state(tdca, cell + cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_axis - 1))                      *alive_neighbors_count += (cell_state(tdca, cell + cells_per_axis - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_axis + 1))                      *alive_neighbors_count += (cell_state(tdca, cell + cells_per_axis + 1) > 0 ? 1 : 0);

    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice))                         *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice - 1))                     *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice + 1))                     *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice + 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice - cells_per_axis))        *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice - cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice - cells_per_axis - 1))    *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice - cells_per_axis - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice - cells_per_axis + 1))    *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice - cells_per_axis + 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice + cells_per_axis))        *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice + cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice + cells_per_axis - 1))    *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice + cells_per_axis - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice + cells_per_axis + 1))    *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice + cells_per_axis + 1) > 0 ? 1 : 0);

    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice))                         *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice - 1))                     *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice + 1))                     *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice + 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice - cells_per_axis))        *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice - cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice - cells_per_axis - 1))    *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice - cells_per_axis - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice - cells_per_axis + 1))    *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice - cells_per_axis + 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice + cells_per_axis))        *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice + cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice + cells_per_axis - 1))    *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice + cells_per_axis - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice + cells_per_axis + 1))    *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice + cells_per_axis + 1) > 0 ? 1 : 0);
}

__device__ void count_alive_neighbors_von_neumann(tdca* tdca, cell_index cell, unsigned int* alive_neighbors_count)
{
    int cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    int cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    if(is_in_bounds_relative(tdca, cell, cell - 1))                                       *alive_neighbors_count += (cell_state(tdca, cell - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + 1))                                       *alive_neighbors_count += (cell_state(tdca, cell + 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_axis))                          *alive_neighbors_count += (cell_state(tdca, cell - cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_axis))                          *alive_neighbors_count += (cell_state(tdca, cell + cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice))                         *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice))                         *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice) > 0 ? 1 : 0);
}

__global__ void update_lifespace_partition(tdca* tdca)
{
    unsigned int thread_id = threadIdx.x;
    unsigned int block_id = blockIdx.x;
    unsigned int number_of_threads_per_block = blockDim.x;
    unsigned int number_of_blocks_per_grid = gridDim.x;

    int cells_per_thread = tdca->lifespace.cell_count / (number_of_threads_per_block * number_of_blocks_per_grid);
    
    cell_index starting_cell = (block_id * (cells_per_thread * number_of_threads_per_block)) + (thread_id * cells_per_thread);
    cell_index ending_cell = starting_cell + cells_per_thread - 1;
    
    for(cell_index cell = starting_cell; cell < ending_cell + 1; cell++)
    {
        unsigned int alive_neighbor_count = 0;
        if(tdca->rule.neighborhood == tdca_rule::MOORE)
        {
            count_alive_neighbors_moore(tdca, cell, &alive_neighbor_count);
        }
        else if(tdca->rule.neighborhood == tdca_rule::VON_NEUMANN)
        {
            count_alive_neighbors_von_neumann(tdca, cell, &alive_neighbor_count);
        }

        if(cell_state(tdca, cell) == tdca_cell::ALIVE)
        {
            if(tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[alive_neighbor_count] == 0)
            {
                if(tdca->rule.state_count == 2)
                {
                    tdca->lifespace.current_cells[cell].state = tdca_cell::DEAD;
                    tdca->lifespace.current_cells[cell].lifetime = 0;
                }
                else
                {
                    tdca->lifespace.current_cells[cell].state = tdca_cell::DYING;
                    tdca->lifespace.current_cells[cell].lifetime--;
                }
            }
        }
        else if(cell_state(tdca, cell) == tdca_cell::DYING)
        {
            if(tdca->lifespace.last_cells[cell].lifetime == 0)
            {
                tdca->lifespace.current_cells[cell].state = tdca_cell::DEAD;
            }
            else
            {
                tdca->lifespace.current_cells[cell].lifetime--;
            }
        }
        else if(cell_state(tdca, cell) == tdca_cell::DEAD)
        {
            if(tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[alive_neighbor_count] == 1)
            {
                tdca->lifespace.current_cells[cell].state = tdca_cell::ALIVE;
                tdca->lifespace.current_cells[cell].lifetime = tdca->rule.state_count - 1;
            }
        }
    }
}

void cuda_update_current_buffer(tdca* tdca)
{
    cudaMemcpy(tdca->lifespace.current_cells, tdca->lifespace.last_cells, sizeof(tdca_cell) * tdca->lifespace.cell_count, cudaMemcpyDefault);

    unsigned int partition_count = 1 << tdca->spacial_partitioning_scheme.subdivision_count;

    update_lifespace_partition<<<partition_count,1024>>>(tdca);
    int error_code = cudaDeviceSynchronize();
}

void cuda_init(tdca** tdca, unsigned int tdca_size_in_bytes)
{
    cudaMallocManaged(tdca, tdca_size_in_bytes);
    (*tdca)->lifespace.subdivision_count = 6;
    // (*tdca)->lifespace.subdivision_count = 7;
    // (*tdca)->lifespace.subdivision_count = 8;
    // (*tdca)->lifespace.subdivision_count = 9;
    (*tdca)->lifespace.cell_count = 1 << ((*tdca)->lifespace.subdivision_count * 3);

    cudaMallocManaged(&(*tdca)->lifespace.current_cells, (*tdca)->lifespace.cell_count * sizeof(tdca_cell));
    cudaMemset(&(*tdca)->lifespace.current_cells, 0, (*tdca)->lifespace.cell_count * sizeof(tdca_cell));

    cudaMallocManaged(&(*tdca)->lifespace.last_cells, (*tdca)->lifespace.cell_count * sizeof(tdca_cell));
    cudaMemset(&(*tdca)->lifespace.last_cells, 0, (*tdca)->lifespace.cell_count * sizeof(tdca_cell));

    (*tdca)->rule.neighborhood = (*tdca)->rule.neighborhood::MOORE;

    (*tdca)->spacial_partitioning_scheme.scheme = (*tdca)->spacial_partitioning_scheme.scheme::BINARY;
    (*tdca)->spacial_partitioning_scheme.subdivision_count = 8;
    // (*tdca)->spacial_partitioning_scheme.subdivision_count = 11;
    // (*tdca)->spacial_partitioning_scheme.subdivision_count = 14;
    // (*tdca)->spacial_partitioning_scheme.subdivision_count = 17;

    cudaMallocManaged(&g_instances, (*tdca)->lifespace.cell_count * sizeof(voxel_instance_transforms));
    cudaMemset(g_instances, 0, (*tdca)->lifespace.cell_count * sizeof(voxel_instance_transforms));
}

void cuda_free(tdca* tdca)
{
    cudaFree(tdca->lifespace.current_cells);
    cudaFree(tdca->lifespace.last_cells);
    cudaFree(tdca);
    cudaFree(g_dx11_voxel);
    cudaFree(g_instances);
}

DirectX::XMVECTOR calculate_cell_position_vector(tdca* tdca, cell_index cell)
{
    cell_index cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    cell_index cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);
    
    real32 x = ((real32) (cell % cells_per_axis)) / (real32) cells_per_axis;
    real32 y = -((real32) (((int32) ((real32) cell / cells_per_axis)) % (cells_per_slice / cells_per_axis)) / (real32) cells_per_axis);
    real32 z = -((real32) ((int32) ((real32) cell / cells_per_slice)) / (real32) cells_per_axis);

    return DirectX::XMVectorSet(x, y, z, 1.0f);
}

void cuda_update_voxels(tdca* tdca)
{
    cell_index alive_cell_counter = 0;
    for(cell_index cell = 0; cell < (real32) tdca->lifespace.cell_count; cell++)
    {
        if(tdca->lifespace.current_cells[cell].state == tdca_cell::ALIVE || tdca->lifespace.current_cells[cell].state == tdca_cell::DYING)
        {
            g_instances[alive_cell_counter].translation = calculate_cell_position_vector(tdca, cell);
            alive_cell_counter++;
        }
    }
    g_dx11_voxel->instance_count = alive_cell_counter;

    cudaGraphicsMapResources(1, &g_graphics_resource, 0);

    voxel_instance_transforms* instance_buffer;
    size_t instance_buffer_size;
    cudaGraphicsResourceGetMappedPointer((void **) &instance_buffer, &instance_buffer_size, g_graphics_resource);

    cudaMemcpy(instance_buffer, g_instances, sizeof(voxel_instance_transforms) * alive_cell_counter, cudaMemcpyDeviceToDevice);

    cudaGraphicsUnmapResources(1, &g_graphics_resource, 0);

    cudaMemcpy(tdca->lifespace.last_cells, tdca->lifespace.current_cells, sizeof(tdca_cell) * tdca->lifespace.cell_count, cudaMemcpyDeviceToDevice);
    cudaMemset(tdca->lifespace.current_cells, 0, sizeof(tdca_cell) * tdca->lifespace.cell_count);
}

void cuda_init_voxel_render_data()
{
    cudaMallocManaged(&g_dx11_voxel, sizeof(voxel_render_data));
}

void cuda_link_instance_buffer()
{
    cudaGraphicsD3D11RegisterResource(&g_graphics_resource, g_dx11_voxel->instance_buffer, 0);
}