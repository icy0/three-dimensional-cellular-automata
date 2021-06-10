#pragma once

void cuda_init(tdca** tdca, unsigned int tdca_size_in_bytes);
void cuda_update_current_buffer(tdca* tdca);
void cuda_free(tdca* tdca);