#pragma once

#include "common.h"

#include <stddef.h>
#include <pthread.h>


extern thread_info_t* threads;

void create_threads(size_t T,
                    size_t N,
                    float* restrict A,
                    float* restrict B,
                    float* restrict C
                    );

void join_threads(size_t T);

void delete_threads(size_t T);
