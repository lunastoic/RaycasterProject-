#include "sphere.h"  // Include the header for sphere definitions

#include <math.h>  // Include for mathematical operations like sqrt and pow

#define INVALID_T -999

// Function to create a new sphere with a given center and radius
Sphere sphere(Tuple center, double radius) {
  Sphere s;
  s.center = center;
  s.radius = radius;
  return s;
}

// Intersection of a sphere with a ray
Isect intersect(Sphere sphere, Ray ray) {
  Isect is;

  // Calculate vector from ray origin to sphere center
  Tuple o_minus_c = subTuples(ray.origin, sphere.center);

  // Calculate the coefficients of the quadratic equation
  double a = dotProduct(ray.direction, ray.direction);
  double b = 2 * dotProduct(ray.direction, o_minus_c);
  double c = dotProduct(o_minus_c, o_minus_c) - pow(sphere.radius, 2);

  // Calculate the discriminant
  double discr = pow(b, 2) - 4 * a * c;

  // Check if the discriminant is negative, which means no real intersections
  if (discr < 0) {
    is.count = 0;
    is.t_vals[0] = INVALID_T;
    is.t_vals[1] = INVALID_T;
    return is;
  }

  // Calculate the two solutions to the quadratic equation
  double t1 = (-b - sqrt(discr)) / (2 * a);
  double t2 = (-b + sqrt(discr)) / (2 * a);

  is.count = 2;
  is.t_vals[0] = t1;
  is.t_vals[1] = t2;

  // Reference the sphere that this intersection relates to
  is.object = sphere;

  return is;
}
