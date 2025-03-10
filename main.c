#include "linked_list.h"
#include <stdio.h>

int main() {
  list_int_t ll = CreateList_int();
  for (int i = 0; i < 10; i++) {
    ListLPush_int(&ll, i);
  }
  node_int_t *current = ll.head;
  while (current) {
    printf("%d\n", current->obj);
    current = current->r;
  }

  return 0;
}
