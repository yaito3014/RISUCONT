/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2024 TwoSquirrels
 */

#include <stdlib.h>

int *new_int(int x) {
  int *p = (int *) malloc(sizeof(int));
  if (p != NULL) *p = x;
  return p;
}

/*#include "maptest.h"*/
#include "settest.h"

#include <stdio.h>

int main(void) {
  /*test_risu_map();*/
  test_risu_set();
  return 0;
}
