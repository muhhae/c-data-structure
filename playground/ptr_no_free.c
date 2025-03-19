#include "../linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int *int_ptr;
DefineLinkedList(int_ptr, NULL);

int main(void) {
    list_int_ptr_t l = CreateList_int_ptr();
    int *a = malloc(sizeof(int));
    *a = 100;
    l.LPush(&l, a);
    printf("l_head = %d addr = %p\n", *l.head->value, l.head->value);
    printf("a = %d addr = %p\n", *a, a);
    printf("\ndestroy\n");
    l.Destroy(&l);
    printf("a = %d addr = %p\n", *a, a);

    // segfault
    // printf("l_head = %d\n", *l.head->value);
    return 0;
}
