#include <stdio.h>

#include "writer.h"

void write_to_csv(int fd, double time) {
  dprintf(fd, "%lf,", time);
}
