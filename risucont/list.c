// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 TwoSquirrels

#include "list.h"

#include <string.h>

typedef struct {
  size_t prv, nxt;
  void *ptr;
} risu_list_node;

risu_list_node risu_list_nodes[RISU_LIST_CAPACITY];
size_t risu_list_nodes_used = 0;

// Iterator for Linked List

void *ref_risu_list(size_t i) {
  return risu_list_nodes[i].ptr;
}
size_t *adv_risu_list(size_t *i, int n) {

}
size_t dist_risu_list(size_t first, size_t last) {

}
size_t next_risu_list(size_t x, int n) {

}
size_t prev_risu_list(size_t x, int n) {

}

// Linked List

risu_list make_risu_list(size_t type_byte, size_t size, const void *value_ptr) {
  risu_list list = malloc(sizeof(risu_list_data));
  if (list == NULL) return NULL;
  list->type_byte = type_byte;
  list->size = size;
  list->front = risu_list_nodes_used;
  list->back = risu_list_nodes_used + size - 1;
  if (list->back >= RISU_LIST_CAPACITY) {
    free(list);
    return NULL;
  }
  char *values_ptr = malloc(type_byte * size);
  if (values_ptr == NULL) {
    free(list);
    return NULL;
  }
  size_t i;
  for (i = list->front; i <= list->back; i++) {
    risu_list_nodes[i].prv = i - 1;
    risu_list_nodes[i].nxt = i + 1;
    risu_list_nodes[i].ptr = values_ptr + type_byte * (i - list->front);
    if (value_ptr != NULL) memcpy(risu_list_nodes[i].ptr, value_ptr, type_byte);
  }
  risu_list_nodes_used = list->back + 1;
  return list;
}

risu_list new_risu_list_c(size_t size, char value) { return make_risu_list(sizeof(char), size, &value); }
risu_list new_risu_list_i(size_t size, int value) { return make_risu_list(sizeof(int), size, &value); }
risu_list new_risu_list_f(size_t size, float value) { return make_risu_list(sizeof(float), size, &value); }
risu_list new_risu_list_d(size_t size, double value) { return make_risu_list(sizeof(double), size, &value); }

void delete_risu_list(risu_list list) {
  //clear_risu_list(list);
  free(list);
}
