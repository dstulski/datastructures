#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hashmap.h"

void hashmap_init(HashMap *hashmap, size_t initial_capacity)
{
	MapNode *init_chains = (MapNode *)malloc(initial_capacity * sizeof(MapNode));
	if (init_chains == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}
	for (size_t i = 0; i < initial_capacity; i++) {
		init_chains[i].key = -1;
		init_chains[i].value = -1;
		init_chains[i].next = NULL;
	}
	hashmap->chains = init_chains;
	hashmap->capacity = initial_capacity;
	hashmap->size = 0;
}

void hashmap_destroy(HashMap *hashmap)
{
	hashmap_clear(hashmap);
	free(hashmap->chains);
}

void hashmap_clear(HashMap *hashmap)
{
	for (size_t i = 0; i < hashmap->capacity; i++) {
		if (hashmap->chains[i].next == NULL) {
			continue;
		}
		MapNode* curr = hashmap->chains[i].next;
		while (curr != NULL) {
			MapNode* next = curr->next;
			free(curr);
			curr = next;
		}
	}
	hashmap->size = 0;
}

static inline int get_hash(int key, size_t capacity)
{
	return key % capacity;
}

static void rechain(MapNode *chains, size_t new_capacity, size_t old_capacity)
{
	for (size_t i = 0; i < old_capacity; i++) {
		MapNode *curr = &chains[i];
		while (curr->next != NULL) {
			int old_hash = get_hash(curr->next->key, old_capacity);
			int new_hash = get_hash(curr->next->key, new_capacity);
			if (old_hash != new_hash) {
				MapNode* node_to_move = curr->next;
				curr->next = node_to_move->next;
				node_to_move->next = chains[new_hash].next;
				chains[new_hash].next = node_to_move;
			}
			curr = curr->next;
		}
	}
}

static void resize(HashMap *hashmap)
{
	size_t new_capacity = hashmap->capacity * 2;
	MapNode *new_chains = (MapNode *)realloc(hashmap->chains, new_capacity * sizeof(MapNode));
	if (new_chains == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}
	for (size_t i = hashmap->capacity - 1; i < new_capacity; i++) {
		new_chains[i].key = -1;
		new_chains[i].value = -1;
		new_chains[i].next = NULL;
	}
	rechain(new_chains, new_capacity, hashmap->capacity);
	hashmap->chains = new_chains;
	hashmap->capacity = new_capacity;
}

void hashmap_set(HashMap *hashmap, int key, int value)
{
	if (hashmap->size > 0.7 * hashmap->capacity) {
		resize(hashmap);
	}
	int hash = get_hash(key, hashmap->capacity);
	MapNode *curr = &hashmap->chains[hash];
	while (curr->next != NULL) {
		if (curr->next->key == key) {
			curr->next->value = value;
			return;
		}
		curr = curr->next;
	}
	MapNode *new_node = (MapNode *)malloc(sizeof(MapNode));
	if (new_node == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	curr->next = new_node;
	hashmap->size++;
}

void hashmap_remove(HashMap *hashmap, int key)
{
	int hash = get_hash(key, hashmap->capacity);
	MapNode *curr = &hashmap->chains[hash];
	while (curr->next != NULL) {
		if (curr->next->key == key) {
			MapNode *node_to_remove = curr->next;
			curr->next = node_to_remove->next;
			free(node_to_remove);
			hashmap->size--;
			return;
		}
	}
}

int hashmap_get(HashMap *hashmap, int key)
{
	int hash = get_hash(key, hashmap->capacity);
	MapNode *curr = &hashmap->chains[hash];
	while (curr->next != NULL) {
		if (curr->next->key == key) {
			return curr->next->value;
		}
	}
	fprintf(stderr, "Key does not exist in HashMap");
	exit(-1);
}

size_t hashmap_size(HashMap *hashmap)
{
	return hashmap->size;
}

