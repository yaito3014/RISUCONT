/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2024 TwoSquirrels
 */

#include "../risucont/map.h"

#include <stdio.h>

void print_risu_map(risu_map *map) {
  risu_map_node *i;
  for (i = map->front; i != NULL; i = i->nxt) {
    printf("%d: %d\n", *(int *) i->key, *(int *) i->value);
  }
}

void dump_risu_map(risu_map *map) {
  risu_map_node *i;
  size_t k;
  for (k = 0; k < RISUCONT_MAP_BUCKET_SIZE; ++k) {
    printf("%d: ", (int) k);
    for (i = map->bucket[k]; i != NULL && i->hash == k; i = i->nxt) {
      printf("%d ", *(int *) i->key);
    }
    printf("\n");
  }
}

void test_risu_map(void) {
  risu_map_node *i;
  int k;
  risu_map *map = new_risu_map(int, int);
  
  puts("\n======== Testing risucont/map.h ========\n");
  
  /* insert */
  for (k = 0; k < 100; ++k) {
    insert_risu_map(map, new_int(k), new_int(k * k));
  }
  puts("INSERTED");
  print_risu_map(map);
  puts("  bucket:");
  dump_risu_map(map);
  puts("----------------------------------------");
  
  /* erase */
  for (i = map->front; i != NULL; ) {
    if (*(int *) i->key % 3 == 0) i = erase_risu_map(map, i);
    else i = i->nxt;
  }
  puts("ERASED");
  print_risu_map(map);
  puts("  bucket:");
  dump_risu_map(map);
  puts("----------------------------------------");
  
  /* find */
  for (k = 0; k < 100; ++k) {
    i = find_risu_map(map, new_int(k));
    if (i != NULL) printf("find %d: %d\n", k, *(int *) i->value);
    else printf("find %d: not found\n", k);
  }
  puts("----------------------------------------");
  
  delete_risu_map(map);
}
