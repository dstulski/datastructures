#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dynamic_array.h"

void dynamic_array_init(DynamicArray *array, size_t initial_capacity)
{
	array->capacity = initial_capacity;
	array->data = (int *)malloc(array->capacity * sizeof(int));
	if (array->data == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}
	array->size = 0;
}

void dynamic_array_free(DynamicArray *array)
{
	free(array->data);
	array->data = NULL;
	array->size = 0;
	array->capacity = 0;
}

void dynamic_array_append(DynamicArray *array, int element)
{
	if (array->size >= array->capacity) {
		size_t new_capacity = array->capacity * 2;
		int *new_data = (int *)realloc(array->data, new_capacity * sizeof(int));
		if (new_data == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			exit(1);
		}
		array->data = new_data;
		array->capacity = new_capacity;
	}
	array->data[array->size++] = element;
}

int dynamic_array_get(DynamicArray *array, size_t index)
{
	if (index >= array->size) {
		fprintf(stderr, "Index out of bounds\n");
		exit(1);
	}
	return array->data[index];
}

void dynamic_array_set(DynamicArray *array, size_t index, int value)
{
	if (index >= array->size) {
		fprintf(stderr, "Index out of bounds\n");
		exit(1);
	}
	array->data[index] = value;
}

size_t dynamic_array_size(DynamicArray *array)
{
	return array->size;
}
