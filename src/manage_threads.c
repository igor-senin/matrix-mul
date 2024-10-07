#include "manage_threads.h"

#include "common.h"
#include "fast_mul.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


thread_info_t* threads;


void create_threads(size_t T,
                    size_t N,
                    float* restrict A,
                    float* restrict B,
                    float* restrict C
                    ) {
  threads = malloc(T * sizeof(thread_info_t));
  if (threads == NULL) {
    perror("malloc: threads");
    exit(EXIT_FAILURE);
  }

  barrier_init(T);

  thread_args_t common = {N, A, B, C, T, 0};
  for (size_t i = 0; i < T; ++i) {
    thread_args_t* args = malloc(sizeof(thread_args_t));
    memcpy(args, &common, sizeof(thread_args_t));
    args->num = i;

    threads[i].args = args;
    pthread_create(&threads[i].thread, NULL, do_multiply, args);
  }
}

void join_threads(size_t T) {
  for (size_t i = 0; i < T; ++i) {
    (void)pthread_join(threads[i].thread, NULL);
  }
}

void delete_threads(size_t T) {
  barrier_destroy(T);
  for (size_t i = 0; i < T; ++i) {
    free(threads[i].args);
  }
  free(threads);
}
