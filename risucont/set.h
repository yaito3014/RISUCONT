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

#endif /* RISUCONT_SET_H */
