#include "fast_mul.h"

#include "common.h"

#include <immintrin.h>
#include <pthread.h>


static pthread_barrier_t barrier;

void barrier_wait() {
  pthread_barrier_wait(&barrier);
}

void barrier_init(size_t T) {
  pthread_barrier_init(&barrier, NULL, T + 1);
}

void barrier_destroy(size_t T) {
  pthread_barrier_destroy(&barrier);
}

void* do_multiply(void* void_args) {
  const size_t s = L1_TILING_GRANULARITY; // 64
  const size_t t = L2_TILING_GRANULARITY; // 8

  thread_args_t* args = void_args;
  size_t N = args->N;
  float* restrict A = args->A;
  float* restrict B = args->B;
  float* restrict C = args->C;
  size_t threads_total = args->T;
  size_t thread_num = args->num;

  const size_t block_dim = N / s; // Будем предполагать, что делится без остатка
  const size_t total_blocks = block_dim * block_dim;

  barrier_wait();

  for (size_t block_idx = thread_num; block_idx < total_blocks; block_idx += threads_total) {
    size_t i1 = (block_idx / block_dim) * s;
    size_t j1 = (block_idx % block_dim) * s;
    for (size_t k1 = 0; k1 < N; k1 += s) {
      for (size_t i2 = 0; i2 < s; i2 += t) {
        for (size_t k2 = 0; k2 < s; k2 += t) {
          for (size_t j2 = 0; j2 < s; j2 += t) {
            for (size_t i3 = 0; i3 < t; ++i3) {
              for (size_t k3 = 0; k3 < t; ++k3) {

                size_t i = i1 + i2 + i3;
                size_t k = k1 + k2 + k3;
                __m256 packA = _mm256_broadcast_ss(A + N*i + k);

                for (size_t j3 = 0; j3 < t; j3 += 8/* =256/32 */) {
                  size_t j = j1 + j2 + j3;
                  /* C[i][j] += A[i][k] * B[k][j] */

                  __m256 packB = _mm256_loadu_ps(B + N*k + j);
                  __m256 packC = _mm256_loadu_ps(C + N*i + j);

                  __m256 packInterm = _mm256_mul_ps(packA, packB);
                  packC = _mm256_add_ps(packC, packInterm);

                  _mm256_storeu_ps(C + N*i + j, packC);
                }
              }
            }
          }
        }
      }
    }
  }
  return NULL;
}

int fast_multiply(size_t N, float* restrict A, float* restrict B, float* restrict C) {
  // Start threads...
  barrier_wait();
  return 0;
}
