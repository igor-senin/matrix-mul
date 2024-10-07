#include "simple_mul.h"

#include <stdint.h>

int simple_multiply(size_t N,
                    float A[N][N],
                    float B[N][N],
                    float C[N][N]
                    ) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      C[i][j] = 0.;
      for (size_t k = 0; k < N; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return 0;
}
