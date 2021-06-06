#include <cstdlib>

#include "tdca_types.h"
#include "renderhub_assert.h"

void configuration_clouds_1(tdca* tdca)
{
    tdca->rule.state_count = 2;
    
    for(int32 cell = 0; cell < tdca->lifespace.cell_count; cell++)
    {
        real32 random_number = (real32) rand() / (real32) RAND_MAX;
        if(random_number > 0.54f)
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

void configuration_clouds_2(tdca* tdca)
{
    tdca->rule.state_count = 2;
    
    for(int32 cell = 0; cell < tdca->lifespace.cell_count; cell++)
    {
        real32 random_number = (real32) rand() / (real32) RAND_MAX;
        if(random_number > 0.35f)
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
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[14] = 1;
}

void configuration_clouds_own1(tdca* tdca)
{
    tdca->rule.state_count = 2;
    
    for(int32 cell = 0; cell < tdca->lifespace.cell_count; cell++)
    {
        real32 random_number = (real32) rand() / (real32) RAND_MAX;
        // if(random_number > 0.05f)
        if(random_number > 0.61f)
        {
            tdca->lifespace.last_cells[cell].state = tdca_cell::ALIVE;
            tdca->lifespace.last_cells[cell].lifetime = tdca->rule.state_count - 1;
        }
    }

    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[10] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[11] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[12] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[13] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[14] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[15] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[16] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[17] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[18] = 1;
    // tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[19] = 1;
    // tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[20] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[21] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[22] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[23] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[24] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[25] = 1;
    // tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[26] = 1;

    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[13] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[14] = 1;
}

void configuration_slow_decay(tdca* tdca)
{
    tdca->rule.state_count = 5;
    
    for(int32 cell = 0; cell < tdca->lifespace.cell_count; cell++)
    {
        real32 random_number = (real32) rand() / (real32) RAND_MAX;
        if(random_number > 0.70f)
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

void configuration_clouds_own2(tdca* tdca)
{
    tdca->rule.state_count = 2;
    
    for(int32 cell = 0; cell < tdca->lifespace.cell_count; cell++)
    {
        real32 random_number = (real32) rand() / (real32) RAND_MAX;
        if(random_number > 0.05f)
        {
            tdca->lifespace.last_cells[cell].state = tdca_cell::ALIVE;
            tdca->lifespace.last_cells[cell].lifetime = tdca->rule.state_count - 1;
        }
    }

    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[10] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[11] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[12] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[13] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[14] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[15] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[16] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[17] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[18] = 1;
    // tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[19] = 1;
    // tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[20] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[21] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[22] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[23] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[24] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[25] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[26] = 1;

    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[13] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[14] = 1;
    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[15] = 1;
}

void configuration_pyroclastic(tdca* tdca)
{
    tdca->rule.state_count = 10;

    cell_index cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    cell_index cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    cell_index cube_middle = (tdca->lifespace.cell_count / 2) - (cells_per_slice / 2) - (cells_per_axis / 2);

    // tdca->lifespace.last_cells[cube_middle].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    // tdca->lifespace.last_cells[cube_middle - 1].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    // tdca->lifespace.last_cells[cube_middle - 2].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    // tdca->lifespace.last_cells[cells_per_slice + cube_middle + 1].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[cells_per_slice + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    // tdca->lifespace.last_cells[cells_per_slice + cube_middle + 2].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[cells_per_slice + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    // tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 1].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    // tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 2].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[-cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    // tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 1].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    // tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 2].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    // tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle + 1].state = tdca_cell::ALIVE;
    // tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
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

void configuration_445(tdca* tdca)
{
    tdca->rule.state_count = 5;

    cell_index cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    cell_index cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    cell_index cube_middle = (tdca->lifespace.cell_count / 2) - (cells_per_slice / 2) - (cells_per_axis / 2);

    tdca->lifespace.last_cells[cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_slice) + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[-cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[-(2 * cells_per_slice) + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[cells_per_axis - cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - (2 * cells_per_slice) + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[cells_per_axis - -(2 * cells_per_slice) + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - (2 * cells_per_slice) + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -cells_per_slice + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle + 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle + 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle - 1].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle - 1].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle + 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle + 2].lifetime = tdca->rule.state_count - 1;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle - 2].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(2 * cells_per_axis) - -(2 * cells_per_slice) + cube_middle - 2].lifetime = tdca->rule.state_count - 1;

    tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[4] = 1;

    tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[4] = 1;
}

void init_tdca(tdca* tdca)
{
    tdca->lifespace.subdivision_count = 6;
    rh_assert(tdca->lifespace.subdivision_count <= (sizeof(tdca->lifespace.cell_count) * 8 / 3));

    tdca->lifespace.cell_count = 1 << (tdca->lifespace.subdivision_count * 3);

    tdca->lifespace.current_cells = new tdca_cell[tdca->lifespace.cell_count];
    rh_assert(tdca->lifespace.current_cells);
    ZeroMemory(tdca->lifespace.current_cells, sizeof(tdca_cell) * tdca->lifespace.cell_count);

    tdca->lifespace.last_cells = new tdca_cell[tdca->lifespace.cell_count];
    rh_assert(tdca->lifespace.last_cells);
    ZeroMemory(tdca->lifespace.last_cells, sizeof(tdca_cell) * tdca->lifespace.cell_count);

    ZeroMemory(&tdca->rule, sizeof(tdca_rule));
    tdca->rule.neighborhood = tdca->rule.neighborhood::MOORE;

    tdca->spacial_partitioning_scheme.scheme = tdca->spacial_partitioning_scheme.scheme::BINARY;
    tdca->spacial_partitioning_scheme.subdivision_count = 0;

    configuration_slow_decay(tdca);
}

uint8 cell_state(tdca* tdca, cell_index cell)
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

bool8 is_in_bounds_relative(tdca* tdca, cell_index origin, cell_index target)
{
    cell_index cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    cell_index cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    // the row of cells the current cell index resides in
    cell_index row_start_cell_inclusive = origin - (origin % cells_per_axis);
    cell_index row_end_cell_inclusive = row_start_cell_inclusive + cells_per_axis - 1;

    // the vertical slice of cells the current cell resides in
    cell_index slice_start_cell_inclusive = origin - (origin % cells_per_slice);
    cell_index slice_end_cell_inclusive = slice_start_cell_inclusive + cells_per_slice - 1;

    cell_index succeeding_slice_start_cell_inclusive = slice_end_cell_inclusive + 1;
    cell_index succeeding_slice_end_cell_inclusive = slice_end_cell_inclusive + cells_per_slice;

    cell_index preceding_slice_start_cell_inclusive = slice_start_cell_inclusive - cells_per_slice;
    cell_index preceding_slice_end_cell_inclusive = slice_start_cell_inclusive - 1;

    int32 difference =  target - origin;

    bool8 cell_is_right =   difference == 1 
                            || difference == -cells_per_axis + 1 
                            || difference == cells_per_axis + 1 
                            || difference == - cells_per_slice + 1 
                            || difference == - cells_per_slice + -cells_per_axis + 1 
                            || difference == - cells_per_slice + cells_per_axis + 1 
                            || difference == + cells_per_slice + 1 
                            || difference == + cells_per_slice + -cells_per_axis + 1 
                            || difference == + cells_per_slice + cells_per_axis + 1;
    
    bool8 cell_is_left =    difference == -1 
                            || difference == -cells_per_axis - 1 
                            || difference == cells_per_axis - 1 
                            || difference == - cells_per_slice - 1 
                            || difference == - cells_per_slice + -cells_per_axis - 1 
                            || difference == - cells_per_slice + cells_per_axis - 1 
                            || difference == + cells_per_slice - 1 
                            || difference == + cells_per_slice + -cells_per_axis - 1 
                            || difference == + cells_per_slice + cells_per_axis - 1;

    bool8 cell_is_top =     difference == -cells_per_axis
                            || difference == -cells_per_axis - 1
                            || difference == -cells_per_axis + 1
                            || difference == -cells_per_axis - cells_per_slice
                            || difference == -cells_per_axis - cells_per_slice - 1
                            || difference == -cells_per_axis - cells_per_slice + 1
                            || difference == -cells_per_axis +  cells_per_slice
                            || difference == -cells_per_axis +  cells_per_slice - 1
                            || difference == -cells_per_axis +  cells_per_slice + 1;

    bool8 cell_is_bottom =  difference == cells_per_axis
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

void count_alive_neighbors(tdca* tdca, cell_index cell, uint32* alive_neighbors_count)
{
    cell_index cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    cell_index cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    if(is_in_bounds_relative(tdca, cell, cell - 1))                                       *alive_neighbors_count += (cell_state(tdca, cell - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + 1))                                       *alive_neighbors_count += (cell_state(tdca, cell + 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_axis))                          *alive_neighbors_count += (cell_state(tdca, cell - cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_axis - 1))                      *alive_neighbors_count += (cell_state(tdca, cell - cells_per_axis - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_axis + 1))                      *alive_neighbors_count += (cell_state(tdca, cell - cells_per_axis + 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_axis))                          *alive_neighbors_count += (cell_state(tdca, cell + cells_per_axis) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_axis - 1))                      *alive_neighbors_count += (cell_state(tdca, cell + cells_per_axis - 1) > 0 ? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_axis + 1))                      *alive_neighbors_count += (cell_state(tdca, cell + cells_per_axis + 1) > 0 ? 1 : 0);

    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice))                         *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice - 1))                     *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice - 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice + 1))                     *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice + 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice - cells_per_axis))        *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice - cells_per_axis) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice - cells_per_axis - 1))    *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice - cells_per_axis - 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice - cells_per_axis + 1))    *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice - cells_per_axis + 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice + cells_per_axis))        *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice + cells_per_axis) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice + cells_per_axis - 1))    *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice + cells_per_axis - 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell - cells_per_slice + cells_per_axis + 1))    *alive_neighbors_count += (cell_state(tdca, cell - cells_per_slice + cells_per_axis + 1) > 0? 1 : 0);

    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice))                         *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice - 1))                     *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice - 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice + 1))                     *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice + 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice - cells_per_axis))        *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice - cells_per_axis) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice - cells_per_axis - 1))    *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice - cells_per_axis - 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice - cells_per_axis + 1))    *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice - cells_per_axis + 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice + cells_per_axis))        *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice + cells_per_axis) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice + cells_per_axis - 1))    *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice + cells_per_axis - 1) > 0? 1 : 0);
    if(is_in_bounds_relative(tdca, cell, cell + cells_per_slice + cells_per_axis + 1))    *alive_neighbors_count += (cell_state(tdca, cell + cells_per_slice + cells_per_axis + 1) > 0? 1 : 0);
}

void update_tdca_binary(tdca* tdca)
{
    memcpy(tdca->lifespace.current_cells, tdca->lifespace.last_cells, sizeof(tdca_cell) * tdca->lifespace.cell_count);

    uint32 partition_count = 1 << tdca->spacial_partitioning_scheme.subdivision_count;
    uint32 cells_per_partition = tdca->lifespace.cell_count / partition_count;

    for(uint32 partition = 0; partition < partition_count; partition++)
    {
        cell_index starting_cell = cells_per_partition * partition;
        cell_index ending_cell = (cells_per_partition * partition) + cells_per_partition - 1;

        for(cell_index cell = starting_cell; cell < ending_cell + 1; cell++)
        {
            uint32 alive_neighbor_count = 0;
            count_alive_neighbors(tdca, cell, &alive_neighbor_count);

            if(cell_state(tdca, cell) == tdca_cell::ALIVE)
            {
                if(tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[alive_neighbor_count] == 0)
                {
                    tdca->lifespace.current_cells[cell].state = tdca_cell::DYING;
                    tdca->lifespace.current_cells[cell].lifetime--;
                    continue;
                }
            }
            else if(cell_state(tdca, cell) == tdca_cell::DYING)
            {
                if(tdca->lifespace.last_cells[cell].lifetime == 0)
                {
                    tdca->lifespace.current_cells[cell].state = tdca_cell::DEAD;
                    continue;
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
                    continue;
                }
            }
        }
    }
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