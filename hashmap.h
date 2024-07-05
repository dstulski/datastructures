#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stddef.h>

typedef struct MapNode {
	int key;
	int value;
	struct MapNode *next;
} MapNode;

typedef struct {
	struct MapNode *chains;
	size_t size;
	size_t capacity;
} HashMap;

void hashmap_init(HashMap *hashmap, size_t initial_capacity);

void hashmap_clear(HashMap *hashmap);

void hashmap_set(HashMap *hashmap, int key, int value);

void hashmap_remove(HashMap *hashmap, int key);

int hashmap_get(HashMap *hashmap, int key);

size_t hashmap_size(HashMap *hashmap);

#endif
