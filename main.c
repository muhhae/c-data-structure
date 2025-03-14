#include "linked_list.h"
#include <stdio.h>

DefineLinkedList(int);
DefineLinkedList(float);

// If you want to store pointer, you need to alias it first
typedef int *int_ptr;
DefineLinkedList(int_ptr);

typedef struct {
  float x, y;
} vector2;

DefineLinkedList(vector2);

int main() {
  list_vector2_t lv = CreateList_vector2();
  for (int i = -5; i < 6; i++) {
    lv.LPush(&lv, (vector2){i, (float)i / 10});
    printf("Pushed (%.2f,%.2f) \ncurrent : [", lv.head->value.x,
           lv.head->value.y);
    for (node_vector2_t *c = lv.head; c != NULL; c = c->r) {
      printf("(%.2f,%.2f)", c->value.x, c->value.y);
      if (c->r)
        printf(", ");
    }
    printf("]\n\n");
  }

  *lv.At(&lv, 2) = (vector2){12, 0.12};

  // SEGFAULT Nil Dereference Error
  // *lv.At(&ll, 99) = (vector2){9, 0.9};
  // printf("99: %d )", *lv.At(&lv, 99));

  printf("\n");
  for (node_vector2_t *c = lv.head; c != NULL; c = c->r) {
    printf("(%.2f,%.2f)\n", c->value.x, c->value.y);
  }
  printf("\n");
  for (size_t i = 0; i < lv.count; i++) {
    printf("%zu : %.2f %.2f\n", i, lv.At(&lv, i)->x, lv.At(&lv, i)->y);
  }
  printf("\n");
  while (lv.count > 0) {
    vector2 popped = lv.LPop(&lv);
    printf("Popped (%.2f,%.2f)\nlv_count: %zu \ncurrent : [", popped.x,
           popped.y, lv.count);
    for (node_vector2_t *c = lv.head; c != NULL; c = c->r) {
      printf("(%.2f,%.2f)", c->value.x, c->value.y);
      if (c->r)
        printf(", ");
    }
    printf("]\n\n");
  }
  printf("last lv_count: %zu", lv.count);

  return 0;
}
