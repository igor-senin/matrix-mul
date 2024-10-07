#pragma once

#include <stddef.h>
#include <pthread.h>

typedef int (*mult_func)(size_t N, float[N][N], float[N][N], float[N][N]);

#define L1_TILING_GRANULARITY 64
#define L2_TILING_GRANULARITY 8


typedef struct {
  size_t N;
  float* restrict A;
  float* restrict B;
  float* restrict C;
  size_t T;
  size_t num;
} thread_args_t;

typedef struct {
  int thread_num;
  pthread_t thread;
  thread_args_t* args;
} thread_info_t;

