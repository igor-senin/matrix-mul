#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "fill_matrices.h"
#include "simple_mul.h"
#include "common.h"
#include "writer.h"


uint64_t timed_multiplication(size_t N,
                              float A[N][N],
                              float B[N][N],
                              float C[N][N],
                              mult_func multiply
                              ) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  (void)multiply(N, A, B, C);

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000
    + (end.tv_nsec - start.tv_nsec) / 1000;

  return delta_us;
}

int main() {

  const size_t N = 512;

  float (*A)[N] = calloc(N, sizeof *A);
  float (*B)[N] = calloc(N, sizeof *A);
  float (*C)[N] = calloc(N, sizeof *A);

  fill_matrices(N, A, B, C);

  int fd = open("results.csv", O_CREAT | O_WRONLY);

  for (size_t n = N; n <= N; n += 128) {
    uint64_t time_i = timed_multiplication(n, A, B, C, simple_multiply);
    double time_d = (double)time_i / 1000.0;
    printf("n = %lu;\ttime = %lf\n", n, time_d);
    // write_to_csv(fd, time_d);
  }

  close(fd);

  free(A);
  free(B);
  free(C);

  return 0;
}
