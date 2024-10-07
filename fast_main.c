#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "manage_threads.h"
#include "fast_mul.h"
#include "fill_matrices.h"
#include "common.h"
#include "writer.h"


const size_t T = 8;

uint64_t timed_multiplication(size_t N,
                              float* restrict A,
                              float* restrict B,
                              float* restrict C
                              ) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  (void)fast_multiply(N, A, B, C);

  join_threads(T);

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000
    + (end.tv_nsec - start.tv_nsec) / 1000;

  return delta_us;
}

int main() {

  const size_t N = 512;

  float* A = malloc(N*N*sizeof(float));
  float* B = malloc(N*N*sizeof(float));
  float* C = malloc(N*N*sizeof(float));

  fill_matrices(N, (float (*)[N])A, (float (*)[N])B, (float (*)[N])C);

  printf("matrices filled\n");

  create_threads(T, N, A, B, C);

  printf("threads created\n");

  // int fd = open("results.csv", O_CREAT | O_WRONLY, 0644);

  uint64_t time_i = timed_multiplication(N, A, B, C);
  double time_d = (double)time_i / 1000.0;
  printf("n = %lu;\ttime = %lf\n", N, time_d);
  // write_to_csv(fd, time_d);

  delete_threads(T);

  // close(fd);

  free(A);
  free(B);
  free(C);

  return 0;
}
