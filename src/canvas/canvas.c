#include "canvas.h"  // Include the header for the canvas functions and structures

#include <assert.h>  // Include for assertions
#include <malloc.h>  // Include for memory allocation functions
#include <stdio.h>   // Include for input/output functions
#include <stdlib.h>  // Include for general utilities
#include <string.h>  // Include for string manipulation functions

// Utility function for conversion of unsigned int to char array
static char *unsigned_int_to_char_array(unsigned int num);

// Function to ensure values stay within the byte range (0-255)
unsigned int clamp_to_byte_range(int value) {
  if (value < 0) return 0;      // Clamp to minimum 0
  if (value > 255) return 255;  // Clamp to maximum 255
  return value;                 // If in range, return original value
}

// Creates a canvas of a given width and height, initializes pixel data
Canvas canvas(unsigned int w, unsigned int h) {
  Canvas c;
  c.width = w;     // Set the canvas width
  c.height = h;    // Set the canvas height
  c.channels = 3;  // Set number of color channels to 3 (Red, Green, Blue)
  c.pixels = calloc(
      3 * w * h,
      sizeof(unsigned int));  // Allocate and initialize pixel data to zero
  return c;                   // Return the created canvas
}

// Writes a pixel with a specified color at a specific location in the canvas
Canvas write_pixel(Canvas ca, unsigned int x, unsigned int y, Color co) {
  if (x < ca.width &&
      y < ca.height) {  // Check if coords are within the canvas bounds
    unsigned int *pix_ptr =
        ca.pixels +
        ca.channels * (y * ca.width + x);  // Calculate the pointer to the pixel
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
  if (x < ca.width &&
      y < ca.height) {  // Check if the coords are within the canvas bounds
    unsigned int *pix_ptr =
        ca.pixels +
        ca.channels * (y * ca.width + x);  // Calculate pointer to the pixel
    color.red = (double)*(pix_ptr);        // Get the red component
    color.green = (double)*(pix_ptr + 1);  // Get the green component
    color.blue = (double)*(pix_ptr + 2);   // Get the blue component
  }
  return color;  // Return the color
}
char *canvas_to_ppm(Canvas ca) {
  const unsigned int HEADER_MAX_LEN = 100;
  char header[HEADER_MAX_LEN];
  snprintf(header, HEADER_MAX_LEN, "P3\n%d %d\n255\n", ca.width, ca.height);

  // Estimate buffer size conservatively, considering max values and
  // space/newline characters
  size_t buffer_size =
      strlen(header) + ca.width * ca.height * 12 + ca.height * 2;
  char *ppm = malloc(buffer_size);
  if (!ppm) return NULL;

  char *curr = ppm;
  curr += sprintf(curr, "%s", header);

  for (unsigned int y = 0; y < ca.height; y++) {
    int line_len = 0;
    for (unsigned int x = 0; x < ca.width; x++) {
      unsigned int index = (y * ca.width + x) * ca.channels;
      char pixel[15];
      snprintf(pixel, sizeof(pixel), "%u %u %u",
               clamp_to_byte_range((int)(ca.pixels[index])),
               clamp_to_byte_range((int)(ca.pixels[index + 1])),
               clamp_to_byte_range((int)(ca.pixels[index + 2])));

      int pixel_len = strlen(pixel);

      // If adding the next pixel would exceed 70 characters, start a new line
      if (line_len + pixel_len + (line_len > 0 ? 1 : 0) > 70) {
        curr += sprintf(curr, "\n%s", pixel);
        line_len = pixel_len;
      } else {
        curr += sprintf(curr, "%s%s", line_len > 0 ? " " : "", pixel);
        line_len += pixel_len + (line_len > 0 ? 1 : 0);
      }
    }
    curr += sprintf(curr, "\n");
  }

  return ppm;
}
