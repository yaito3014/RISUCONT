/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2024 TwoSquirrels
 */

#include "../risucont/set.h"

#include <stdio.h>

void print_risu_set_int(risu_set *set) {
  risu_set_node *i;
  for (i = set->front; i != NULL; i = i->nxt) {
    printf("%d\n", *(int *) i->key);
  }
}

int is_dump_on = 0;
void dump_risu_set_int(risu_set *set) {
  risu_set_node *i;
  size_t k;
  if (!is_dump_on) {
    puts("(dump is off)");
    return;
  }
  for (k = 0; k < RISUCONT_MAP_BUCKET_SIZE; ++k) {
    printf("%d: ", (int) k);
    for (i = set->bucket[k]; i != NULL && i->hash == k; i = i->nxt) {
      printf("%d ", *(int *) i->key);
    }
    printf("\n");
  }
}

void print_risu_set_pair_int(risu_set *set) {
  risu_set_node *i;
  for (i = set->front; i != NULL; i = i->nxt) {
    printf("(%d, %d)\n", *(int *) ((risu_set_pair *) i->key)->key0, *(int *) ((risu_set_pair *) i->key)->key1);
  }
}

void print_risu_set_union_int(risu_set *set) {
  risu_set_node *i;
  for (i = set->front; i != NULL; i = i->nxt) {
    printf("(%d, %d)\n", *(int *) ((risu_set_union *) i->key)->key, ((risu_set_union *) i->key)->index);
  }
}

void print_risu_set_set_int(risu_set *set) {
  risu_set_node *i, *j;
  for (i = set->front; i != NULL; i = i->nxt) {
    printf("{ ");
    for (j = ((risu_set *) i->key)->front; j != NULL; j = j->nxt) {
      printf("%d, ", *(int *) j->key);
    }
    printf("}\n");
  }
}

void test_risu_set(void) {
  risu_set_node *i;
  int k;
  risu_set *set = new_risu_set(int), *set1 = new_risu_set(int), *result;
  
  puts("\n======== Testing risucont/set.h ========\n");
  
  /* insert */
  for (k = 0; k < 100; ++k) {
    insert_risu_set(set, new_int(k));
  }
  puts("INSERTED");
  print_risu_set_int(set);
  puts("  bucket:");
  dump_risu_set_int(set);
  puts("----------------------------------------");
  
  /* erase */
  for (i = set->front; i != NULL; ) {
    if (*(int *) i->key % 5 != 0) i = erase_risu_set(set, i);
    else i = i->nxt;
  }
  puts("ERASED");
  print_risu_set_int(set);
  puts("  bucket:");
  dump_risu_set_int(set);
  puts("----------------------------------------");
  
  /* find */
  for (k = 0; k < 100; ++k) {
    i = find_risu_set(set, new_int(k));
    if (i != NULL) printf("find %d\n", k);
  }
  
  /* ---------------------------------------- */
  
  for (k = 20; k < 80; k += 10) {
    insert_risu_set(set1, new_int(k));
  }
  puts("SET1");
  print_risu_set_int(set1);
  puts("----------------------------------------");
  
  /* is_subset */
  puts("IS_SUBSET");
  printf("set is_subset set1: %s\n", is_subset_risu_set(set, set1) ? "true" : "false");
  printf("set1 is_subset set: %s\n", is_subset_risu_set(set1, set) ? "true" : "false");
  puts("----------------------------------------");
  
  /* is_disjoint */
  puts("IS_DISJOINT");
  printf("set is_disjoint set1: %s\n", is_disjoint_risu_set(set, set1) ? "true" : "false");
  puts("----------------------------------------");
  
  insert_risu_set(set1, new_int(46));
  puts("SET1");
  print_risu_set_int(set1);
  puts("----------------------------------------");
  
  /* intersect */
  puts("INTERSECT");
  result = intersect_risu_set(set1, set);
  printf("result size: %d\n", (int) result->size);
  print_risu_set_int(result);
  delete_risu_set(result);
  puts("----------------------------------------");
  
  /* union */
  puts("UNION");
  result = unite_risu_set(set, set1);
  printf("result size: %d\n", (int) result->size);
  print_risu_set_int(result);
  delete_risu_set(result);
  puts("----------------------------------------");
  
  /* difference */
  puts("DIFFERENCE");
  result = difference_risu_set(set, set1);
  printf("set-set1 size: %d\n", (int) result->size);
  print_risu_set_int(result);
  delete_risu_set(result);
  result = difference_risu_set(set1, set);
  printf("set1-set size: %d\n", (int) result->size);
  print_risu_set_int(result);
  delete_risu_set(result);
  puts("----------------------------------------");
  
  /* symmetric_difference */
  puts("SYMMETRIC_DIFFERENCE");
  result = symmetric_difference_risu_set(set, set1);
  printf("result size: %d\n", (int) result->size);
  print_risu_set_int(result);
  delete_risu_set(result);
  puts("----------------------------------------");
  
  /* cartesian_product */
  puts("CARTESIAN_PRODUCT");
  result = cartesian_product_risu_set(set, set1);
  printf("result size: %d\n", (int) result->size);
  print_risu_set_pair_int(result);
  delete_risu_set(result);
  puts("----------------------------------------");
  
  /* disjoint_union */
  puts("DISJOINT_UNION");
  result = disjoint_union_risu_set(set, set1);
  printf("result size: %d\n", (int) result->size);
  print_risu_set_union_int(result);
  delete_risu_set(result);
  puts("----------------------------------------");
  
  /* power_set */
  puts("POWER_SET");
  result = power_set_risu_set(set1);
  printf("result size: %d\n", (int) result->size);
  print_risu_set_set_int(result);
  delete_risu_set(result);
  puts("----------------------------------------");
  
  delete_risu_set(set);
  delete_risu_set(set1);
}
