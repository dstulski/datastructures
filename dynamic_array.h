#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

// data structure definition
typedef struct
{
	int *data;
	size_t size;
	size_t capacity;
} DynamicArray;

// function prototypes

// initialize the dynamic array
void dynamic_array_init(DynamicArray *array, size_t initial_capacity);

// free the memory allocated for the dynamic array
void dynamic_array_free(DynamicArray *array);

// append element to the dynamic array
void dynamic_array_append(DynamicArray *array, int element);

// get the element at an index
int dynamic_array_get(DynamicArray *array, size_t index);

// set the element at an index
void dynamic_array_set(DynamicArray *array, size_t index, int value);

// get the current size of the dynamic array
size_t dynamic_array_size(DynamicArray *array);

#endif
