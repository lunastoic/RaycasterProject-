#include "hits.h"

#include <stdlib.h>  // For malloc and free

IRec intersection(double t, Sphere object) {
  IRec i;
  i.t = t;
  i.object = object;
  return i;
}

IRecs intersections(unsigned int count, ...) {
  IRecs xs;
  xs.count = count;
  xs.records = malloc(count * sizeof(IRec));
  if (xs.records == NULL) {
    // Handle memory allocation failure
    xs.count = 0;
    return xs;
  }

  va_list args;
  va_start(args, count);
  for (unsigned int i = 0; i < count; i++) {
    xs.records[i] = va_arg(args, IRec);
  }
  va_end(args);

  return xs;
}

IRec hit(IRecs xs) {
  IRec hit;
  hit.t = INVALID_T;

  for (unsigned int i = 0; i < xs.count; i++) {
    if (xs.records[i].t >= 0 &&
        (hit.t == INVALID_T || xs.records[i].t < hit.t)) {
      hit = xs.records[i];
    }
  }

  return hit;
}
