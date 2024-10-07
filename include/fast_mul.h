#pragma once

#include <stddef.h>
#include <pthread.h>

void barrier_wait();
void barrier_init(size_t T);
void barrier_destroy(size_t T);

void* do_multiply(void* args);

int fast_multiply(size_t N,
                  float* restrict A,
                  float* restrict B,
                  float* restrict C
                  );
