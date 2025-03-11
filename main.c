#include "linked_list.h"
#include <stdio.h>

LinkedList(int);
LinkedList(float);

typedef struct {
  float x, y;
} vector2;

LinkedList(vector2);

int main() {
  list_float_t lf = CreateList_float();
  list_int_t ll = CreateList_int();
  list_vector2_t lv = CreateList_vector2();
  for (int i = -5; i < 6; i++) {
    ll.LPush(&ll, i);
    lf.LPush(&lf, (float)i / 10);
    lv.LPush(&lv, (vector2){i, (float)i / 10});
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

  printf("\nVector2\n\n");
  node_vector2_t *current_v = lv.head;
  while (current_v) {
    printf("%f %f\n", current_v->obj.x, current_v->obj.y);
    current_v = current_v->r;
  }
  printf("\n");
  current_v = lv.tail;
  while (current_v) {
    printf("%f %f\n", current_v->obj.x, current_v->obj.y);
    current_v = current_v->l;
  }
  printf("\n");
  for (int i = 0; i < lv.count; i++) {
    printf("%d : %f %f\n", i, lv.At(&lv, i)->obj.x, lv.At(&lv, i)->obj.y);
  }

  return 0;
}
