#include "fill_matrices.h"

#include <stdint.h>
#include <stdlib.h>

// Generates random float with EXP = 0 using rand(),
// i.e. floats in form (-1)^s * 1.xxxx... * 2^0.
// abs(get_random_float()) is in [1.0, 2.0).
static float get_random_float() {
  uint32_t sign = (rand() & 1) << 31;
  uint32_t exponent = 0x7f << 23;
  uint32_t significand = rand() & 0x7fffff;

  union {
    float    fres;
    uint32_t ires;
  } conv = { .ires = 0 };
  conv.ires |= sign;
  conv.ires |= exponent;
  conv.ires |= significand;

  return conv.fres;
}

void fill_matrices(size_t N, float A[N][N], float B[N][N], float C[N][N]) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      A[i][j] = get_random_float();
      B[i][j] = get_random_float();
      C[i][j] = 0.f;
    }
  }
}
