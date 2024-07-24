/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2024 TwoSquirrels
 */

#include "../risucont/set.h"

#include <stdio.h>

void print_risu_set(risu_set *set) {
  risu_set_node *i;
  for (i = set->front; i != NULL; i = i->nxt) {
    printf("%d\n", *(int *) i->key);
  }
}

void dump_risu_set(risu_set *set) {
  risu_set_node *i;
  size_t k;
  for (k = 0; k < RISUCONT_MAP_BUCKET_SIZE; ++k) {
    printf("%d: ", (int) k);
    for (i = set->bucket[k]; i != NULL && i->hash == k; i = i->nxt) {
      printf("%d ", *(int *) i->key);
    }
    printf("\n");
  }
}

void test_risu_set(void) {
  risu_set_node *i;
  int k;
  risu_set *set = new_risu_set(int);
  
  puts("\n======== Testing risucont/set.h ========\n");
  
  /* insert */
  for (k = 0; k < 100; ++k) {
    insert_risu_set(set, new_int(k));
  }
  puts("INSERTED");
  print_risu_set(set);
  puts("  bucket:");
  dump_risu_set(set);
  puts("----------------------------------------");
  
  /* erase */
  for (i = set->front; i != NULL; ) {
    if (*(int *) i->key % 3 == 0) i = erase_risu_set(set, i);
    else i = i->nxt;
  }
  puts("ERASED");
  print_risu_set(set);
  puts("  bucket:");
  dump_risu_set(set);
  puts("----------------------------------------");
  
  /* find */
  for (k = 0; k < 100; ++k) {
    i = find_risu_set(set, new_int(k));
    if (i != NULL) printf("find %d\n", k);
  }
  
  delete_risu_set(set);
}
