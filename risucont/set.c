/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2024 TwoSquirrels
 */

#include "set.h"

#include <string.h>

/* Operations */

int is_subset_risu_set(risu_set *set0, risu_set *set1) {
  risu_set_node *i;
  for (i = set0->front; i != NULL; i = i->nxt) {
    if (find_risu_set(set1, i->key) == NULL) return 0;
  }
  return 1;
}

int is_proper_subset_risu_set(risu_set *set0, risu_set *set1) {
  return set0->size < set1->size && is_subset_risu_set(set0, set1);
}

int is_equal_risu_set(risu_set *set0, risu_set *set1) {
  return set0->size == set1->size && is_subset_risu_set(set0, set1);
}

int is_disjoint_risu_set(risu_set *set0, risu_set *set1) {
  risu_set_node *i;
  for (i = set0->front; i != NULL; i = i->nxt) {
    if (find_risu_set(set1, i->key) != NULL) return 0;
  }
  return 1;
}

risu_set *intersect_risu_set(risu_set *set0, risu_set *set1) {
  risu_set *result = make_risu_set(set0->key_byte);
  risu_set_node *i;
  if (result == NULL) return NULL;
  for (i = set0->front; i != NULL; i = i->nxt) {
    if (find_risu_set(set1, i->key) != NULL) {
      if (insert_cpy_risu_set(result, i->key) == NULL) {
        delete_risu_set(result);
        return NULL;
      }
    }
  }
  return result;
}

risu_set *unite_risu_set(risu_set *set0, risu_set *set1) {
  risu_set *result = make_risu_set(set0->key_byte);
  risu_set_node *i;
  if (result == NULL) return NULL;
  for (i = set0->front; i != NULL; i = i->nxt) {
    if (insert_cpy_risu_set(result, i->key) == NULL) {
      delete_risu_set(result);
      return NULL;
    }
  }
  for (i = set1->front; i != NULL; i = i->nxt) {
    if (insert_cpy_risu_set(result, i->key) == NULL) {
      delete_risu_set(result);
      return NULL;
    }
  }
  return result;
}

risu_set *difference_risu_set(risu_set *set0, risu_set *set1) {
  risu_set *result = make_risu_set(set0->key_byte);
  risu_set_node *i;
  if (result == NULL) return NULL;
  for (i = set0->front; i != NULL; i = i->nxt) {
    if (find_risu_set(set1, i->key) == NULL) {
      if (insert_cpy_risu_set(result, i->key) == NULL) {
        delete_risu_set(result);
        return NULL;
      }
    }
  }
  return result;
}

risu_set *symmetric_difference_risu_set(risu_set *set0, risu_set *set1) {
  risu_set *result = make_risu_set(set0->key_byte);
  risu_set_node *i;
  if (result == NULL) return NULL;
  for (i = set0->front; i != NULL; i = i->nxt) {
    if (find_risu_set(set1, i->key) == NULL) {
      if (insert_cpy_risu_set(result, i->key) == NULL) {
        delete_risu_set(result);
        return NULL;
      }
    }
  }
  for (i = set1->front; i != NULL; i = i->nxt) {
    if (find_risu_set(set0, i->key) == NULL) {
      if (insert_cpy_risu_set(result, i->key) == NULL) {
        delete_risu_set(result);
        return NULL;
      }
    }
  }
  return result;
}

risu_set *cartesian_product_risu_set(risu_set *set0, risu_set *set1) {
  risu_set *result = new_risu_set(risu_set_pair);
  risu_set_node *i, *j;
  for (i = set0->front; i != NULL; i = i->nxt) {
    for (j = set1->front; j != NULL; j = j->nxt) {
      risu_set_pair *pair = malloc(sizeof(risu_set_pair));
      if (pair == NULL) {
        delete_risu_set(result);
        return NULL;
      }
      pair->key0 = malloc(set0->key_byte);
      pair->key1 = malloc(set1->key_byte);
      if (pair->key0 == NULL || pair->key1 == NULL) {
        free(pair->key0);
        free(pair->key1);
        free(pair);
        delete_risu_set(result);
        return NULL;
      }
      memcpy(pair->key0, i->key, set0->key_byte);
      memcpy(pair->key1, j->key, set1->key_byte);
      if (insert_risu_set(result, pair) == NULL) {
        free(pair->key0);
        free(pair->key1);
        free(pair);
        delete_risu_set(result);
        return NULL;
      }
    }
  }
  return result;
}

risu_set *disjoint_union_risu_set(risu_set *set0, risu_set *set1) {
  risu_set *result = new_risu_set(risu_set_union);
  risu_set_node *i;
  if (result == NULL) return NULL;
  for (i = set0->front; i != NULL; i = i->nxt) {
    risu_set_union *pair = malloc(sizeof(risu_set_union));
    if (pair == NULL) {
      delete_risu_set(result);
      return NULL;
    }
    pair->key = malloc(set0->key_byte);
    if (pair->key == NULL) {
      free(pair);
      delete_risu_set(result);
      return NULL;
    }
    memcpy(pair->key, i->key, set0->key_byte);
    pair->index = 0;
    if (insert_risu_set(result, pair) == NULL) {
      free(pair->key);
      free(pair);
      delete_risu_set(result);
      return NULL;
    }
  }
  for (i = set1->front; i != NULL; i = i->nxt) {
    risu_set_union *pair = malloc(sizeof(risu_set_union));
    if (pair == NULL) {
      delete_risu_set(result);
      return NULL;
    }
    pair->key = malloc(set1->key_byte);
    if (pair->key == NULL) {
      free(pair);
      delete_risu_set(result);
      return NULL;
    }
    memcpy(pair->key, i->key, set1->key_byte);
    pair->index = 1;
    if (insert_risu_set(result, pair) == NULL) {
      free(pair->key);
      free(pair);
      delete_risu_set(result);
      return NULL;
    }
  }
  return result;
}

risu_set *power_set_risu_set(risu_set *set) {
  risu_set *result = new_risu_set(risu_set);
  risu_set_node *i;
  size_t bit;
  if (result == NULL) return NULL;
  if (set->size > sizeof(size_t) * 8) {
    delete_risu_set(result);
    return NULL;
  }
  for (bit = 0; bit < (((size_t) 1) << set->size); ++bit) {
    risu_set *subset = new_risu_set(set->key_byte);
    size_t k = 0;
    if (subset == NULL) {
      delete_risu_set(result);
      return NULL;
    }
    for (i = set->front; i != NULL; i = i->nxt) {
      if (bit & (1 << k)) {
        if (insert_cpy_risu_set(subset, i->key) == NULL) {
          delete_risu_set(subset);
          delete_risu_set(result);
          return NULL;
        }
      }
      ++k;
    }
    if (insert_risu_set(result, subset) == NULL) {
      delete_risu_set(subset);
      delete_risu_set(result);
      return NULL;
    }
  }
  return result;
}
