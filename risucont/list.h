// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 TwoSquirrels

#ifndef RISU_CONTAINERS_LIST_H
#  define RISU_CONTAINERS_LIST_H

#include <stdlib.h>

#ifndef RISU_LIST_CAPACITY
#  define RISU_LIST_CAPACITY ((size_t) 0x10000)
#endif

// Iterator for Linked List

extern void *ref_risu_list(size_t i);
extern size_t *adv_risu_list(size_t *i, int n);
extern size_t dist_risu_list(size_t first, size_t last);
extern size_t next_risu_list(size_t x, int n);
extern size_t prev_risu_list(size_t x, int n);

// Linked List

typedef struct {
  size_t type_byte;
  size_t size;
  size_t front, back;
} risu_list_data;
typedef risu_list_data * risu_list;

extern risu_list make_risu_list(size_t type_byte, size_t size, const void *value_ptr);
#define new_risu_list(TYPE, SIZE) (make_risu_list(sizeof(TYPE), (SIZE), NULL))
#define init_risu_list(SIZE, VALUE_PTR) (make_risu_list(sizeof(*VALUE_PTR), (SIZE), (VALUE_PTR)))
extern risu_list new_risu_list_c(size_t size, char value);
extern risu_list new_risu_list_i(size_t size, int value);
extern risu_list new_risu_list_ll(size_t size, long long value);
extern risu_list new_risu_list_f(size_t size, float value);
extern risu_list new_risu_list_d(size_t size, double value);
extern risu_list new_risu_list_ld(size_t size, long double value);
extern risu_list copy_risu_list(risu_list list);
extern risu_list assign_risu_list(size_t begin, size_t end);
extern void delete_risu_list(risu_list list);

// Iterators
extern size_t begin_risu_list(risu_list list);
extern size_t end_risu_list(risu_list list);
extern size_t rbegin_risu_list(risu_list list);
extern size_t rend_risu_list(risu_list list);

// Capacity
extern char empty_risu_list(risu_list list);
extern size_t size_risu_list(risu_list list);
extern void resize_risu_list(risu_list list, size_t size);

// Element access
extern void *front_risu_list(risu_list list);
extern void *back_risu_list(risu_list list);

// Modifiers
extern void push_front_risu_list(risu_list list, const void *x_ptr);
extern void push_back_risu_list(risu_list list, const void *x_ptr);
extern size_t insert_risu_list(risu_list list, size_t position, void *x_ptr);
extern size_t insert_list_risu_list(risu_list list, size_t position, size_t first, size_t last);
extern void pop_front_risu_list(risu_list list);
extern void pop_back_risu_list(risu_list list);
extern size_t erase_risu_list(risu_list list, size_t position);
extern size_t erase_list_risu_list(risu_list list, size_t first, size_t last);
extern void clear_risu_list(risu_list list);

// Operations
extern size_t splice_risu_list(risu_list list, size_t position, size_t first, size_t last);
extern size_t remove_risu_list(risu_list list, void *value_ptr);
extern size_t unique_risu_list(risu_list list);
extern void reverse_risu_list(risu_list list);

#endif // RISU_CONTAINERS_LIST_H
