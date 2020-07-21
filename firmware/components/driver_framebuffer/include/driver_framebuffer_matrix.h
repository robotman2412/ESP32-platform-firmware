#pragma once

#include "sdkconfig.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "esp_system.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 * This file is NOT part of an external library but is rather created and maintained by RobotMan2412 and the badge team.
 * 
 * DO NOT TOUCH THIS FILE UNLESS YOU UNDERSTAND MATRICES!
 */


/* ==== DATA TYPES ==== */


typedef double matrix_var;

typedef union matrix_2d_t {					// Used by the driver for 2D transformations
	struct {								// Represented as struct where aN is top row and bN is bottom row
		matrix_var a0, a1, a2;				//    and 0 is left column, 1 is middle column, 2 is right column
		matrix_var b0, b1, b2;
	} var;
	matrix_var arr[6];						// Represented as array where index 0->2 is top row, index 3->5 is bottom row
} matrix_2d;

typedef union matrix_3d_t {					// Used by driver for 3D transformations
	struct {
		matrix_var a0, a1, a2, a3;
		matrix_var b0, b1, b2, b3;
		matrix_var c0, c1, c2, c3;
	} var;
	matrix_var arr[12];
} matrix_3d;

typedef struct matrix_stack_3d_t {
	uint16_t capacity;						// How many matrices the current stack can hold in total
	uint16_t size;							// How many matrices are currently on the stack
	matrix_3d *matrices;					// The matrix array
    matrix_3d current;						// The active matrix
} matrix_stack_3d;

typedef float depth_buffer_type;			// Whatever will get stored in the depth buffer

typedef struct graphics_stack_3d_t {		// The 3D graphics stack, includes everything required for 3D
	matrix_stack_3d *stack;					// The 3D matrix stack
	depth_buffer_type *depth_buffer;        // The depth buffer, it allows to easily sort polygons by which one is on top
	int width;								// The width of the depth buffer
	int height;								// The height of the depth buffer
} graphics_stack_3d;

typedef struct matrix_stack_2d_t {
	uint16_t capacity;						// How many matrices the current stack can hold in total
	uint16_t size;							// How many matrices are currently on the stack
	matrix_2d *matrices;					// The matrix array
    matrix_2d current;						// The active matrix
} matrix_stack_2d;



/* ==== HELPER MACROS ==== */


//creates the 2D identity matrix
#define matrix_2d_identity() ((matrix_2d) { .arr = {1, 0, 0, 0, 1, 0} })


/* ==== HELPER FUNCTIONS ==== */


//creates a 2D matrix representing the given rotation in radians
matrix_2d matrix_2d_rotate(double angle);

//creates a 2D matrix representing the given translation
matrix_2d matrix_2d_translate(double x, double y);

//creates a 2D matrix representing the given scaling
matrix_2d matrix_2d_scale(double x, double y);

// Potentially.
// matrix_3x2_2d matrix_2d_shear(double x, double y);


/* ==== MATRIX OPERATIONS ==== */


//performs a matrix multiplication, internally factors in the bottom row which is omitted in storage
matrix_2d matrix_2d_multiply(matrix_2d left, matrix_2d right);

//transforms the point according to the matrix
void matrix_2d_transform_point(matrix_2d matrix, double *x, double *y);


/* ==== STACK OPERATIONS ==== */


//initialises the given matrix stack so as to be ready for use
void matrix_stack_2d_init(matrix_stack_2d *stack);

//clears the matrix stack
//WARNING: This assumes the stack is already initialised!
void matrix_stack_2d_clear(matrix_stack_2d *stack);

//returns ESP_ERROR if the stack would become too big
esp_err_t matrix_stack_2d_push(matrix_stack_2d *stack);

//returns ESP_ERROR if the stack is already empty
esp_err_t matrix_stack_2d_pop(matrix_stack_2d *stack);

#ifdef __cplusplus
}
#endif
