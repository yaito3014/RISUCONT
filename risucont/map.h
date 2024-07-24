/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2024 TwoSquirrels
 */

#ifndef RISUCONT_MAP_H
#  define RISUCONT_MAP_H

#include <stdlib.h>
#include <stdint.h>

/* Hashed Map Node */

/*
 * The log2 of the number of buckets in the hashed map.
 * If you want to change the number of buckets, add -D RISUCONT_MAP_BUCKET_SIZE_LOG2=7 to the compiler options.
 */
#ifndef RISUCONT_MAP_BUCKET_SIZE_LOG2
#  define RISUCONT_MAP_BUCKET_SIZE_LOG2 (13)
#endif

#define RISUCONT_MAP_BUCKET_SIZE (((size_t) 1) << (RISUCONT_MAP_BUCKET_SIZE_LOG2))

typedef struct risu_map_node risu_map_node;
struct risu_map_node {
  risu_map_node *prv, *nxt; /* previous and next node */
  size_t hash; /* hash value */
  void *key, *value; /* key and value (they have ownership) */
};

/* Iterator for Hashed Map */

/* Advances the iterator by n steps. (time: O(n)) */
extern risu_map_node *adv_risu_map(risu_map_node **i, int n);
/* Returns the number of elements between first and last. (time: O(size)) */
extern size_t dist_risu_map(risu_map_node *first, risu_map_node *last);
/* Return the nth successor of the iterator. (time: O(n)) */
extern risu_map_node *next_risu_map(risu_map_node *i, int n);
/* Return the nth predecessor of the iterator. (time: O(n)) */
extern risu_map_node *prev_risu_map(risu_map_node *i, int n);

/* Hashed Map */

typedef struct {
  size_t key_byte, value_byte; /* size of key and value */
  size_t size; /* number of elements */
  risu_map_node *bucket[RISUCONT_MAP_BUCKET_SIZE]; /* bucket list */
  risu_map_node *front, *back; /* front and back of the list */
} risu_map;

/* create a new map (time: O(BUCKET_SIZE)) */
extern risu_map *make_risu_map(size_t key_byte, size_t value_byte);
/* create a new map with a key type (time: O(BUCKET_SIZE)) */
#define new_risu_map(KEY_TYPE, VALUE_TYPE) make_risu_map(sizeof(KEY_TYPE), sizeof(VALUE_TYPE))
/* copy the map (time: O(size)) */
extern risu_map *copy_risu_map(risu_map *map);
/* delete the map (time: O(size)) */
extern void delete_risu_map(risu_map *map);

/* Modifiers */

/* delete all elements in the map (time: O(size)) */
extern void clear_risu_map(risu_map *map);
/* insert a new element into the map (key and value are moved) (time: O(1)) */
extern risu_map_node *insert_risu_map(risu_map *map, void *key, void *value);
/* insert a new element into the map (key is copied and value is moved) (time: O(1)) */
extern risu_map_node *insert_cpykey_risu_map(risu_map *map, void *key, void *value);
/* insert a new element into the map (key is moved and value is copied) (time: O(1)) */
extern risu_map_node *insert_cpyvalue_risu_map(risu_map *map, void *key, void *value);
/* insert a new element into the map (key and value are copied) (time: O(1)) */
extern risu_map_node *insert_cpy_risu_map(risu_map *map, void *key, void *value);
/* erase an element from the map (time: O(1)) */
extern risu_map_node *erase_risu_map(risu_map *map, risu_map_node *i);
/* swap two maps (time: O(BUCKET_SIZE)) */
extern void swap_risu_map(risu_map *map, risu_map *target);
/* merge two maps (All elements in the source that are not in the map are moved to the map) (time: O(source->size)) */
extern int merge_risu_map(risu_map *map, risu_map *source);

/* Lookup */

/* find an element in the map by key (time: O(1)) */
extern risu_map_node *find_risu_map(risu_map *map, void *key);

#endif /* RISUCONT_MAP_H */
