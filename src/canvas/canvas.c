#include "canvas.h"  // Include the header for the canvas functions and structures

#include <assert.h>  // Include for assertions
#include <malloc.h>  // Include for memory allocation functions
#include <stdio.h>   // Include for input/output functions
#include <stdlib.h>  // Include for general utilities
#include <string.h>  // Include for string manipulation functions

static char *unsigned_int_to_char_array(unsigned int);

// Creates a canvas of a given width and height, initializes pixel data
Canvas canvas(unsigned int w, unsigned int h) {
  Canvas c;
  c.width = w;     // Set the canvas width
  c.height = h;    // Set the canvas height
  c.channels = 3;  // Set number of color channels to 3 (RGB)
  c.pixels = calloc(
      3 * w * h,
      sizeof(unsigned int));  // Allocate and initialize pixel data to zero
  return c;                   // Return the created canvas
}

// Writes a pixel with a specified color at a specific location in the canvas
Canvas write_pixel(Canvas ca, unsigned int x, unsigned int y, Color co) {
  if (x < ca.width && y < ca.height) {
    unsigned int *pix_ptr = ca.pixels + ca.channels * (y * ca.width + x);
    *(pix_ptr) = (unsigned int)round(co.red * 255.0);  // Set red component
    *(pix_ptr + 1) =
        (unsigned int)round(co.green * 255.0);  // Set green component
    *(pix_ptr + 2) =
        (unsigned int)round(co.blue * 255.0);  // Set blue component
  }
  return ca;  // Return the updated canvas
}

// Retrieves the color of a pixel at a specified location in the canvas
Color pixel_at(Canvas ca, unsigned int x, unsigned int y) {
  Color color = {0.0, 0.0, 0.0};  // Default color is black
  if (x < ca.width && y < ca.height) {
    unsigned int *pix_ptr = ca.pixels + ca.channels * (y * ca.width + x);
    color.red = (double)*(pix_ptr);        // Get the red component
    color.green = (double)*(pix_ptr + 1);  // Get the green component
    color.blue = (double)*(pix_ptr + 2);   // Get the blue component
  }
  return color;  // Return the color
}
// Converts the entire canvas into a PPM formatted string
char *canvas_to_ppm(Canvas ca) {
  const unsigned int HEADER_MAX_LEN = 100;
  char header[HEADER_MAX_LEN];
  sprintf(header, "P3\n%d %d\n255\n\0", ca.width, ca.height);
  unsigned int hbytes = strlen(header);

  // Allocate memory for the entire PPM data, including space for newlines after
  // each row
  char *ppm =
      calloc(hbytes + (4 * 3 * ca.width * ca.height) + ca.height, sizeof(char));
  if (ppm == NULL) {
    return NULL;  // Return NULL if memory allocation fails
  }
  strcpy(ppm, header);  // Start the PPM data with the header

  // Iterate over each pixel, convert to a string, and concatenate to the PPM
  // data
  for (unsigned int y = 0; y < ca.height; y++) {
    for (unsigned int x = 0; x < ca.width; x++) {
      unsigned int index = (y * ca.width + x) * ca.channels;
      for (int channel = 0; channel < 3; ++channel) {
        char *color = unsigned_int_to_char_array(ca.pixels[index + channel]);
        strcat(ppm, color);
        free(
            color);  // Remember to free the malloc'd string to avoid memoryleak
      }
    }
    strcat(ppm, "\n");  // Append a newline at the end of each row of pixels
  }

  return ppm;  // Return the complete PPM data
}

/* utility for conversion of unsigned int to char array */
static char *unsigned_int_to_char_array(unsigned int num) {
  // function only needs to expect numbers from 0 - 255
  assert(num <= 255 && num >= 0);
  char *str = malloc(4 * sizeof(char));  // Allocate space for at most three
  // digits and a null terminator
  if (str == NULL) {
    return NULL;  // Handle malloc failure
  }
  sprintf(
      str, "%u ",
      num);  // Format the number as a string, including a for PPM formatting
  return str;
}
