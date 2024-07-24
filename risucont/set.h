/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2024 TwoSquirrels
 */

#ifndef RISUCONT_SET_H
#  define RISUCONT_SET_H

#include "map.h"

/* Hashed Set Node */

typedef risu_map_node risu_set_node;

/* Iterator for Hashed Map */

/* Advances the iterator by n steps. (time: O(n)) */
#define adv_risu_set(I, N) (adv_risu_map((I), (N)))
/* Returns the number of elements between first and last. (time: O(size)) */
#define dist_risu_set(FIRST, LAST) (dist_risu_map((FIRST), (LAST)))
/* Return the nth successor of the iterator. (time: O(n)) */
#define next_risu_set(I, N) (next_risu_map((I), (N)))
/* Return the nth predecessor of the iterator. (time: O(n)) */
#define prev_risu_set(I, N) (prev_risu_map((I), (N)))

/* Hashed Set */

typedef risu_map risu_set;

/* create a new set (time: O(BUCKET_SIZE)) */
#define make_risu_set(KEY_BYTE) (make_risu_map((KEY_BYTE), 0))
/* create a new set with a key type (time: O(BUCKET_SIZE)) */
#define new_risu_set(KEY_TYPE) (make_risu_map(sizeof(KEY_TYPE), 0))
/* copy the set (time: O(size)) */
#define copy_risu_set(SET) (copy_risu_map(SET))
/* delete the set (time: O(size)) */
#define delete_risu_set(SET) (delete_risu_map(SET))

/* Modifiers */

/* delete all elements in the set (time: O(size)) */
#define clear_risu_set(SET) (clear_risu_map(SET))
/* insert a new element into the set (time: O(1)) */
#define insert_risu_set(SET, KEY) (insert_risu_map((SET), (KEY), NULL))
/* insert a new element into the set (key is copied) (time: O(1)) */
#define insert_cpy_risu_set(SET, KEY) (insert_cpykey_risu_map((SET), (KEY), NULL))
/* erase the element from the set (time: O(1)) */
#define erase_risu_set(SET, KEY) (erase_risu_map((SET), (KEY)))
/* swap two sets (time: O(BUCKET_SIZE)) */
#define swap_risu_set(SET, TARGET) (swap_risu_map((SET), (TARGET)))
/* merge two sets (All elements in the source that are not in the set are moved to the set) (time: O(source->size)) */
#define merge_risu_set(SET, SOURCE) (merge_risu_map((SET), (SOURCE)))

/* Lookup */

/* find an element in the set by key (time: O(1)) */
#define find_risu_set(SET, KEY) (find_risu_map((SET), (KEY)))

/* Operations */

/* check if the set0 is a subset of another set0 (time: O(set0->size)) */
extern int is_subset_risu_set(risu_set *set0, risu_set *set1);
/* check if the set0 is a proper subset of another set0 (time: O(set0->size)) */
extern int is_proper_subset_risu_set(risu_set *set0, risu_set *set1);
/* check if the set0 is equal to another set0 (time: O(set0->size)) */
extern int is_equal_risu_set(risu_set *set0, risu_set *set1);
/* check if the set0 is disjoint from another set0 (time: O(set0->size)) */
extern int is_disjoint_risu_set(risu_set *set0, risu_set *set1);

typedef struct {
  void *key0;
  void *key1;
} risu_set_pair;

typedef struct {
  void *key;
  int index;
} risu_set_union;

/* solve the intersection of two sets (time: O(set0->size + set1->size)) */
extern risu_set *intersect_risu_set(risu_set *set0, risu_set *set1);
/* solve the union of two sets (time: O(set0->size + set1->size)) */
extern risu_set *unite_risu_set(risu_set *set0, risu_set *set1);
/* solve the difference of two sets (time: O(set0->size + set1->size)) */
extern risu_set *difference_risu_set(risu_set *set0, risu_set *set1);
/* solve the symmetric difference of two sets (time: O(set0->size + set1->size)) */
extern risu_set *symmetric_difference_risu_set(risu_set *set0, risu_set *set1);
/* solve the cartesian product of two sets (time: O(set0->size * set1->size)) */
extern risu_set *cartesian_product_risu_set(risu_set *set0, risu_set *set1);
/* solve the disjoint union of two sets (time: O(set0->size + set1->size)) */
extern risu_set *disjoint_union_risu_set(risu_set *set0, risu_set *set1);
/* solve the power set of the set (time: O(2^set->size)) */
extern risu_set *power_set_risu_set(risu_set *set);

#endif /* RISUCONT_SET_H */
