#include "ray.h"

// Function to create a Ray from an origin point and direction vector
Ray ray(Tuple origin, Tuple direction) {
  Ray r;
  r.origin = origin;
  r.direction = direction;
  return r;
}

// Function to compute the position of the Ray at distance t
Tuple position(Ray r, double t) {
  Tuple offset = scalarMultTuple(t, r.direction);
  return addTuples(r.origin, offset);
}
