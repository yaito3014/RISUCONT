/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2024 TwoSquirrels
 */

#include "map.h"

#include <string.h>

/* swap macros */
#define swap_int(X, Y) ((X) ^= (Y), (Y) ^= (X), (X) ^= (Y))
#define swap(TYPE, X, Y) do { TYPE swap_tmp = X; (X) = (Y); (Y) = swap_tmp; } while (0)
#define swap_ptr(X, Y) swap(void *, (X), (Y))

/* simple hash function */
size_t hash(void *key, size_t key_byte) {
  size_t h = 0, i;
  for (i = 0; i < key_byte; ++i) h = h * 0x1f + ((unsigned char *) key)[i];
  return h % RISUCONT_MAP_BUCKET_SIZE;
}

/* Iterator for Hashed Map */

risu_map_node *adv_risu_map(risu_map_node **i, int n) {
  int k;
  if (n >= 0) for (k = 0; k < n && *i != NULL; ++k) *i = (*i)->nxt;
  else for (k = 0; k < -n && *i != NULL; ++k) *i = (*i)->prv;
  return *i;
}

size_t dist_risu_map(risu_map_node *first, risu_map_node *last) {
  size_t n = 0;
  risu_map_node *i;
  for (i = first; i != last; i = i->nxt) {
    if (i == NULL) return -1;
    ++n;
  }
  return n;
}

risu_map_node *next_risu_map(risu_map_node *i, int n) {
  return adv_risu_map(&i, n);
}

risu_map_node *prev_risu_map(risu_map_node *i, int n) {
  return adv_risu_map(&i, -n);
}

/* Hashed Map */

risu_map *make_risu_map(size_t key_byte, size_t value_byte) {
  risu_map *map = (risu_map *) malloc(sizeof(risu_map));
  if (map == NULL) return NULL;
  map->key_byte = key_byte;
  map->value_byte = value_byte;
  map->size = 0;
  memset(map->bucket, 0, sizeof(map->bucket));
  map->front = NULL;
  map->back = NULL;
  return map;
}

risu_map *copy_risu_map(risu_map *map) {
  risu_map_node *i;
  risu_map *copy = make_risu_map(map->key_byte, map->value_byte);
  if (copy == NULL) return NULL;
  for (i = map->front; i != NULL; i = i->nxt) {
    void *key = malloc(map->key_byte);
    void *value = malloc(map->value_byte);
    if (key == NULL || value == NULL) {
      free(key);
      free(value);
      delete_risu_map(copy);
      return NULL;
    }
    memcpy(key, i->key, map->key_byte);
    memcpy(value, i->value, map->value_byte);
    if (insert_risu_map(copy, key, value)) {
      free(key);
      free(value);
      delete_risu_map(copy);
      return NULL;
    }
  }
  return copy;
}

void delete_risu_map(risu_map *map) {
  clear_risu_map(map);
  free(map);
}

/* Modifiers */

void clear_risu_map(risu_map *map) {
  risu_map_node *i, *nxt;
  for (i = map->front; i != NULL; i = nxt) {
    nxt = i->nxt;
    free(i->key);
    free(i->value);
    free(i);
  }
  map->size = 0;
  memset(map->bucket, 0, sizeof(map->bucket));
  map->front = NULL;
  map->back = NULL;
}

risu_map_node *insert_risu_map(risu_map *map, void *key, void *value) {
  size_t h = hash(key, map->key_byte);
  risu_map_node *node = find_risu_map(map, key);
  if (node != NULL) {
    free(node->key);
    free(node->value);
    node->key = key;
    node->value = value;
    return node;
  }
  node = (risu_map_node *) malloc(sizeof(risu_map_node));
  if (node == NULL) {
    free(key);
    free(value);
    return NULL;
  }
  node->prv = (map->bucket[h] == NULL) ? map->back : map->bucket[h]->prv;
  node->nxt = map->bucket[h];
  node->hash = h;
  node->key = key;
  node->value = value;
  if (node->prv == NULL) map->front = node;
  else node->prv->nxt = node;
  if (node->nxt == NULL) map->back = node;
  else node->nxt->prv = node;
  ++map->size;
  return map->bucket[h] = node;
}

risu_map_node *insert_cpykey_risu_map(risu_map *map, void *key, void *value) {
  void *key_cpy = malloc(map->key_byte);
  if (key_cpy == NULL) {
    free(value);
    return NULL;
  }
  memcpy(key_cpy, key, map->key_byte);
  return insert_risu_map(map, key_cpy, value);
}

risu_map_node *insert_cpyvalue_risu_map(risu_map *map, void *key, void *value) {
  void *value_cpy = malloc(map->value_byte);
  if (value_cpy == NULL) {
    free(key);
    return NULL;
  }
  memcpy(value_cpy, value, map->value_byte);
  return insert_risu_map(map, key, value_cpy);
}

risu_map_node *insert_cpy_risu_map(risu_map *map, void *key, void *value) {
  void *key_cpy = malloc(map->key_byte);
  if (key_cpy == NULL) return NULL;
  memcpy(key_cpy, key, map->key_byte);
  return insert_cpyvalue_risu_map(map, key_cpy, value);
}

risu_map_node *erase_risu_map(risu_map *map, risu_map_node *i) {
  risu_map_node *nxt = i->nxt;
  if (map->bucket[i->hash] == i) map->bucket[i->hash] = nxt;
  if (i->prv == NULL) map->front = i->nxt;
  else i->prv->nxt = i->nxt;
  if (i->nxt == NULL) map->back = i->prv;
  else i->nxt->prv = i->prv;
  free(i->key);
  free(i->value);
  free(i);
  --map->size;
  return nxt;
}

void swap_risu_map(risu_map *map, risu_map *target) {
  size_t i;
  swap_int(map->key_byte, target->key_byte);
  swap_int(map->value_byte, target->value_byte);
  swap_int(map->size, target->size);
  for (i = 0; i < RISUCONT_MAP_BUCKET_SIZE; ++i) swap_ptr(map->bucket[i], target->bucket[i]);
  swap_ptr(map->front, target->front);
  swap_ptr(map->back, target->back);
}

int merge_risu_map(risu_map *map, risu_map *source) {
  risu_map_node *i;
  for (i = source->front; i != NULL; i = i->nxt) {
    if (find_risu_map(map, i->key) == NULL) {
      if (insert_risu_map(map, i->key, i->value) == NULL) return -1;
      i->key = NULL;
      i->value = NULL;
      erase_risu_map(source, i);
    }
  }
  return 0;
}

/* Lookup */

risu_map_node *find_risu_map(risu_map *map, void *key) {
  size_t h = hash(key, map->key_byte);
  risu_map_node *i;
  for (i = map->bucket[h]; i != NULL && i->hash == h; i = i->nxt) {
    if (memcmp(i->key, key, map->key_byte) == 0) return i;
  }
  return NULL;
}
