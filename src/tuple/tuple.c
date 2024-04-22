#include "tuple.h"
#include <math.h>

unsigned int is_point(Tuple t) {
    return t.w == 1.0;
}
unsigned int is_vector(Tuple t) {
    return t.w == 0.0;
}
// Function to create a new tuple
Tuple tuple(double x, double y, double z, double w) {
    Tuple t; // Declare a Tuple variable 't'
    t.x = x; // Assign the value of 'x' to the 'x' component of 't'
    t.y = y; // Assign the value of 'y' to the 'y' component of 't'
    t.z = z; // Assign the value of 'z' to the 'z' component of 't'
    t.w = w; // Assign the value of 'w' to the 'w' component of 't', determines if it's a point or vector
    return t; // Return the Tuple 't'
}

// Function to create a new point
Tuple point(double x, double y, double z) {
    Tuple t; // Declare a Tuple variable 't'
    t.x = x; // Set the x-coordinate of the point
    t.y = y; // Set the y-coordinate of the point
    t.z = z; // Set the z-coordinate of the point
    t.w = 1.0; // Set 'w' to 1.0, indicating that this is a point
    return t; // Return the created point
}

// Function to create a new vector
Tuple vector(double x, double y, double z) {
    Tuple t; // Declare a Tuple variable 't'
    t.x = x; // Set x-component of the vector
    t.y = y; // Set y-component of the vector
    t.z = z; // Set z-component of the vector
    t.w = 0.0; // Set 'w' to 0.0, indicating that this is a vector
    return t; // Return the created vector
}

// Function to add two tuples
Tuple addTuples(Tuple a, Tuple b) {
    Tuple result; // declares a new tuple named result
    result.x = a.x + b.x; //adds x comp of the input tuple a and b and assigns the sum of x comp of the 'result' tuple
    result.y = a.y + b.y; //adds y comp of the input tuple a and b and assigns the sum of y comp of the 'result' tuple
    result.z = a.z + b.z; //adds z comp of the input tuple a and b and assigns the sum of z comp of the 'result' tuple
    result.w = a.w + b.w; //adds w comp of the input tuple a and b and assigns the sum of w comp of the 'result' tuple
    return result; //returns the 'tuple' which contains the sum of comps of the input tuples
}
// Function to subtract two tuples
Tuple subTuples(Tuple a, Tuple b) {
    Tuple t; // Declare a Tuple variable 't' for the result.
    t.x = a.x - b.x; // Sub x-component of b from a.
    t.y = a.y - b.y; // Sub y-component of b from a.
    t.z = a.z - b.z; // Sub z-component of b from a.
    t.w = a.w - b.w; // Sub w-component of b from a.
    return t; // Return the resulting Tuple.
}

// Function to negate a tuple
Tuple negateTuple(Tuple t) {
    Tuple result; // Declare a Tuple variable 'result' for the negated tuple.
    result.x = -t.x; // Negate the x-component of tuple t.
    result.y = -t.y; // Negate the y-component of tuple t.
    result.z = -t.z; // Negate the z-component of tuple t.
    result.w = -t.w; // Negate the w-component of tuple t.
    return result; // Return the negated tuple.
}

// Function to multiply a tuple by a scalar
Tuple scalarMultTuple(double scalar, Tuple t) {
    Tuple result; // Declare a Tuple variable 'result' for the scaled tuple.
    result.x = t.x * scalar; // Multi x-component of t by scalar.
    result.y = t.y * scalar; // Multi y-component of t by scalar.
    result.z = t.z * scalar; // Multi z-component of t by scalar.
    result.w = t.w * scalar; // Multi w-component of t by scalar.
    return result; // Return the scaled tuple.
}

// Function to divide a tuple by a scalar
Tuple scalarDivideTuple(Tuple t, double scalar) {
    Tuple result; // Declare a Tuple variable 'result' for the divided tuple.
    result.x = t.x / scalar; // Div x-component of t by scalar.
    result.y = t.y / scalar; // Div y-component of t by scalar.
    result.z = t.z / scalar; // Div z-component of t by scalar.
    result.w = t.w / scalar; // Div w-component of t by scalar.
    return result; // Return the divided tuple.
}

// Function to compute the magnitude of a vector
double magnitudeOfVector(Tuple a) {
    // cal the sq root of the sum suqares of x,y,z comps
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// Function to normalize a vector
Tuple normalizeVector(Tuple a) {
    double mag = magnitudeOfVector(a); //computer the mag of the vector
    return scalarDivideTuple(a, mag); //divide each comp of the vector by its mag to create a unit of vector
}

// Function to compute the dot product of two vectors
double dotProduct(Tuple a, Tuple b) {
    //cal the dot product of two tuples or vecs by times componetns
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}



// Function to create a new color
Color color(double red, double green, double blue) {
    Color c;
    c.red = red; //red = red color
    c.green = green; //green = green color
    c.blue = blue; // blue = blue color
    return c; // return color
}
//add two colors 
Color addColors(Color a, Color b) {
    Color c;
    c.red = a.red + b.red; //add a and b red
    c.green = a.green + b.green;// add a and b green
    c.blue = a.blue + b.blue;// add a and b blue
    return c;
}
//sub one color from another 
Color subColors(Color a, Color b) {
    Color c;
    c.red = a.red - b.red; //sub a and b red
    c.green = a.green - b.green;// sub a and b green
    c.blue = a.blue - b.blue;// sud a and b blue
    return c;
}
//mutl colors with scalar value
Color scalarMultColor(double scalar, Color color)
{
    Color result;
    result.red = color.red * scalar; //times red with scalar val
    result.green = color.green * scalar;//times green with scalar val
    result.blue = color.blue * scalar; //times blue with scalar val
    return result;
}
//times two colors
Color multColors(Color a, Color b) {
    Color c; //declare a color variable c for the result
    c.red = a.red * b.red; //times red components of a and b
    c.green = a.green * b.green;//times green componetns of a and b
    c.blue = a.blue * b.blue; // times blue components of a and b
    return c;
}