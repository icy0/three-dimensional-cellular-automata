#include <cstdio>
#include <cstdlib>

#include "tdca_types.h"

__device__ unsigned int cell_state(tdca* tdca, int cell)
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

__device__ bool is_in_bounds_relative(tdca* tdca, int origin, int target)
{
    int cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    int cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    // the row of cells the current cell index resides in
    int row_start_cell_inclusive = origin - (origin % cells_per_axis);
    int row_end_cell_inclusive = row_start_cell_inclusive + cells_per_axis - 1;

    // the vertical slice of cells the current cell resides in
    int slice_start_cell_inclusive = origin - (origin % cells_per_slice);
    int slice_end_cell_inclusive = slice_start_cell_inclusive + cells_per_slice - 1;

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

__device__ void count_alive_neighbors_moore(tdca* tdca, int cell, unsigned int* alive_neighbors_count)
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

__device__ void count_alive_neighbors_von_neumann(tdca* tdca, int cell, unsigned int* alive_neighbors_count)
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
    
    int starting_cell = (block_id * (cells_per_thread * number_of_threads_per_block)) + (thread_id * cells_per_thread);
    int ending_cell = starting_cell + cells_per_thread - 1;
    
    for(int cell = starting_cell; cell < ending_cell + 1; cell++)
    {
        unsigned int alive_neighbor_count = 0;
        if(tdca->rule.neighborhood == tdca_rule::MOORE)
        {
            count_alive_neighbors_moore(tdca, cell, &alive_neighbor_count); // make device function
        }
        else if(tdca->rule.neighborhood == tdca_rule::VON_NEUMANN)
        {
            count_alive_neighbors_von_neumann(tdca, cell, &alive_neighbor_count); // make device function
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
    int dummy = 42;
}

void cuda_init(tdca** tdca, unsigned int tdca_size_in_bytes)
{
    cudaMallocManaged(tdca, tdca_size_in_bytes);
    (*tdca)->lifespace.subdivision_count = 6;
    (*tdca)->lifespace.cell_count = 1 << ((*tdca)->lifespace.subdivision_count * 3);

    cudaMallocManaged(&(*tdca)->lifespace.current_cells, (*tdca)->lifespace.cell_count * sizeof(tdca_cell));
    // cudaMemset(&tdca->lifespace.current_cells, 0, tdca->lifespace.cell_count * sizeof(tdca_cell));

    cudaMallocManaged(&(*tdca)->lifespace.last_cells, (*tdca)->lifespace.cell_count * sizeof(tdca_cell));
    // cudaMemset(&tdca->lifespace.last_cells, 0, tdca->lifespace.cell_count * sizeof(tdca_cell));

    (*tdca)->rule.neighborhood = (*tdca)->rule.neighborhood::MOORE;

    (*tdca)->spacial_partitioning_scheme.scheme = (*tdca)->spacial_partitioning_scheme.scheme::BINARY;
    (*tdca)->spacial_partitioning_scheme.subdivision_count = 6;
}

void cuda_free(tdca* tdca)
{
    cudaFree(tdca->lifespace.current_cells);
    cudaFree(tdca->lifespace.last_cells);
}