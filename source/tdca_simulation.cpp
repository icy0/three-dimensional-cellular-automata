#include <cstdlib>

#include "tdca_types.h"
#include "renderhub_assert.h"

void init_tdca(tdca* tdca)
{
    tdca->lifespace.subdivision_count = 5;
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
    tdca->rule.state_count = 2;

    tdca->lifespace.last_cells[0].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[0].lifetime = tdca->rule.state_count - 1;

    uint32 cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    uint32 cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    tdca->lifespace.last_cells[tdca->lifespace.cell_count / 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[tdca->lifespace.cell_count / 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice + 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice + 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice + 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice + 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice - 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice - 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice - 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) + cells_per_slice - 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice + 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice + 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice + 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice + 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice - 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice - 1 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice - 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].state = tdca_cell::ALIVE;
    tdca->lifespace.last_cells[(tdca->lifespace.cell_count / 2) - cells_per_slice - 2 + (cells_per_slice / 2) + (cells_per_axis / 2)].lifetime = tdca->rule.state_count - 1;

    for(uint8 neighbor = 0; neighbor < 26; neighbor++)
    {
        if(neighbor == 6 || neighbor == 7 || neighbor == 8)
        {
            tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[neighbor] = 0b1;
        }
        if(neighbor == 6 || neighbor == 7 || neighbor == 8)
        {
            tdca->rule.necessary_amounts_of_alive_neighbors_for_birth[neighbor] = 0b1;
        }
    }

    tdca->spacial_partitioning_scheme.scheme = tdca->spacial_partitioning_scheme.scheme::BINARY;
    tdca->spacial_partitioning_scheme.subdivision_count = 0;
}

uint8 cell_state(tdca* tdca, uint32 cell)
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

void count_alive_neighbors(tdca* tdca, uint32 cell, uint32* alive_neighbors_count)
{
    uint32 cells_per_axis = 1 << tdca->lifespace.subdivision_count;
    uint32 cells_per_slice = 1 << (tdca->lifespace.subdivision_count * 2);

    *alive_neighbors_count += cell_state(tdca, cell - 1);
    *alive_neighbors_count += cell_state(tdca, cell + 1);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_axis);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_axis - 1);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_axis + 1);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_axis);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_axis - 1);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_axis + 1);

    *alive_neighbors_count += cell_state(tdca, cell - cells_per_slice);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_slice - 1);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_slice + 1);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_slice - cells_per_axis);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_slice - cells_per_axis - 1);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_slice - cells_per_axis + 1);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_slice + cells_per_axis);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_slice + cells_per_axis - 1);
    *alive_neighbors_count += cell_state(tdca, cell - cells_per_slice + cells_per_axis + 1);

    *alive_neighbors_count += cell_state(tdca, cell + cells_per_slice);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_slice - 1);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_slice + 1);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_slice - cells_per_axis);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_slice - cells_per_axis - 1);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_slice - cells_per_axis + 1);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_slice + cells_per_axis);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_slice + cells_per_axis - 1);
    *alive_neighbors_count += cell_state(tdca, cell + cells_per_slice + cells_per_axis + 1);
}

void update_tdca_binary(tdca* tdca)
{
    uint32 partition_count = 1 << tdca->spacial_partitioning_scheme.subdivision_count;
    uint32 cells_per_partition = tdca->lifespace.cell_count / partition_count;

    for(uint32 partition = 0; partition < partition_count; partition++)
    {
        uint32 starting_cell = cells_per_partition * partition;
        uint32 ending_cell = (cells_per_partition * partition) + cells_per_partition - 1;

        for(uint32 cell = starting_cell; cell < ending_cell + 1; cell++)
        {
            uint32 alive_neighbor_count = 0;
            count_alive_neighbors(tdca, cell, &alive_neighbor_count);

            if(cell_state(tdca, cell) == tdca_cell::ALIVE)
            {
                if(tdca->rule.necessary_amounts_of_alive_neighbors_for_surviving[alive_neighbor_count] == 0)
                {
                    if(tdca->lifespace.last_cells[cell].lifetime >= 1)
                    {
                        tdca->lifespace.current_cells[cell].lifetime--;
                    }
                    if(tdca->lifespace.last_cells[cell].lifetime == 1)
                    {
                        tdca->lifespace.current_cells[cell].state = tdca_cell::DEAD;
                    }
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