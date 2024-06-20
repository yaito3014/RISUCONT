// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 TwoSquirrels

#include "../risucont/list.h"

#include <stdio.h>

int main() {
  risu_list list = new_risu_list_i(8, 3);
  printf("list: type_byte=%lu, size=%lu, front=%lu, back=%lu\n", list->type_byte, list->size, list->front, list->back);
  return 0;
}
