#include "linked_list.h"
#include <stdio.h>

LinkedList(int);
LinkedList(float);

int main() {
  list_float_t lf = CreateList_float();
  list_int_t ll = CreateList_int();
  for (int i = -5; i < 6; i++) {
    ll.LPush(&ll, i);
    lf.LPush(&lf, (float)i / 10);
  }

  printf("Int\n\n");
  node_int_t *current = ll.head;
  while (current) {
    printf("%d\n", current->obj);
    current = current->r;
  }
  printf("\n");
  current = ll.tail;
  while (current) {
    printf("%d\n", current->obj);
    current = current->l;
  }
  printf("\n");
  for (int i = 0; i < ll.count; i++) {
    printf("%d : %d\n", i, ll.At(&ll, i)->obj);
  }

  printf("\nFloat\n\n");
  node_float_t *current_f = lf.head;
  while (current_f) {
    printf("%f\n", current_f->obj);
    current_f = current_f->r;
  }
  printf("\n");
  current_f = lf.tail;
  while (current_f) {
    printf("%f\n", current_f->obj);
    current_f = current_f->l;
  }
  printf("\n");
  for (int i = 0; i < lf.count; i++) {
    printf("%d : %f\n", i, lf.At(&lf, i)->obj);
  }

  return 0;
}
