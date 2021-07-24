#include <cstdlib>

#include "tdca_types.h"
#include "renderhub_assert.h"

#include "tdca_gpu_device_functions.h"

void update_tdca_binary(tdca* tdca);
void update_tdca_octree(tdca* tdca);
void update_tdca(tdca* tdca);
void configuration_clouds_1(tdca* tdca);
void configuration_pyroclastic(tdca* tdca);
void configuration_slow_decay(tdca* tdca);

tdca* init_tdca(tdca* tdca_p)
{
    cuda_init(&tdca_p, sizeof(tdca));
    configuration_clouds_1(tdca_p);
    return tdca_p;
}

void reset_tdca(tdca* tdca)
{
    ZeroMemory(tdca->lifespace.last_cells, tdca->lifespace.cell_count * sizeof(tdca_cell));
    configuration_clouds_1(tdca);
}

void update_tdca_binary(tdca* tdca)
{
    cuda_update_current_buffer(tdca);
}

void update_tdca_octree(tdca* tdca)
{

}

void update_tdca(tdca* tdca)
{
    switch(tdca->spacial_partitioning_scheme.scheme)
    {
        case(tdca_spacial_partitioning_scheme::BINARY):
        {
            update_tdca_binary(tdca);
            break;
        }
        case(tdca_spacial_partitioning_scheme::OCTREE):
        {
            update_tdca_octree(tdca);
            break;
        }
    }
}

void configuration_clouds_1(tdca* tdca)
{
    tdca->rule.state_count = 2;

    
    for(int32 cell = 0; cell < (int32) tdca->lifespace.cell_count; cell++)
    {
        rh_assert(cell < 0xFFFFFFFF / 2);
        real32 random_number = (real32) rand() / (real32) RAND_MAX;
        if(random_number > 0.48f)
        {
            tdca->lifespace.last_cells[cell].state = tdca_cell::ALIVE;
            tdca->lifespace.last_cells[cell].lifetime = tdca->rule.state_count - 1;
        }
    }

    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[13] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[14] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[15] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[16] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[17] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[18] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[19] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[20] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[21] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[22] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[23] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[24] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[25] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[26] = 1;

    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[13] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[16] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[17] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[18] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[19] = 1;
}

void configuration_slow_decay(tdca* tdca)
{
    tdca->rule.state_count = 5;
    
    for(int32 cell = 0; cell < (real32) tdca->lifespace.cell_count; cell++)
    {
        rh_assert(cell < 0xFFFFFFFF / 2);
        real32 random_number = (real32) rand() / (real32) RAND_MAX;
        if(random_number > 0.71f)
        {
            tdca->lifespace.last_cells[cell].state = tdca_cell::ALIVE;
            tdca->lifespace.last_cells[cell].lifetime = tdca->rule.state_count - 1;
        }
    }

    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[1] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[4] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[8] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[11] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[13] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[14] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[15] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[16] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[17] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[18] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[19] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[20] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[21] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[22] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[23] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[24] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[25] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[26] = 1;

    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[13] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[14] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[15] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[16] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[17] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[18] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[19] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[20] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[21] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[22] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[23] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[24] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[25] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[26] = 1;
}

void configuration_pyroclastic(tdca* tdca)
{
    tdca->rule.state_count = 10;

    cell_index cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    cell_index cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    cell_index cube_middle = (tdca->lifespace.cell_count / 2) - (cells_per_slice / 2) - (cells_per_axis / 2);

    tdca->lifespace.last_cells[cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[4] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[5] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[6] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[7] = 1;

    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[6] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[7] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[8] = 1;
}