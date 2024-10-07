#pragma once

#include <stddef.h>

static float get_random_float();

void fill_matrices(size_t N,
                   float A[N][N],
                   float B[N][N],
                   float C[N][N]
                   );
