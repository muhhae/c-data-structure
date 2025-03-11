#ifndef MUHHAE_LINKED_LIST_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_TYPE(TYPE) node_##TYPE##_t
#define LIST_TYPE(TYPE) list_##TYPE##_t

#define LL_FUNCTION(TYPE)                                                      \
  struct NODE_TYPE(TYPE);                                                      \
  struct LIST_TYPE(TYPE);                                                      \
  typedef struct NODE_TYPE(TYPE) NODE_TYPE(TYPE);                              \
  typedef struct LIST_TYPE(TYPE) LIST_TYPE(TYPE);                              \
  typedef void (*ll_lpush_func_##TYPE)(LIST_TYPE(TYPE) *, TYPE);               \
  typedef void (*ll_rpush_func_##TYPE)(LIST_TYPE(TYPE) *, TYPE);               \
  typedef NODE_TYPE(TYPE) * (*ll_at_func_##TYPE)(LIST_TYPE(TYPE) *, size_t);

#define NODE(TYPE)                                                             \
  struct NODE_TYPE(TYPE) {                                                     \
    TYPE obj;                                                                  \
    struct NODE_TYPE(TYPE) * l;                                                \
    struct NODE_TYPE(TYPE) * r;                                                \
  };

#define LIST(TYPE)                                                             \
  struct LIST_TYPE(TYPE) {                                                     \
    NODE_TYPE(TYPE) * head;                                                    \
    NODE_TYPE(TYPE) * tail;                                                    \
    size_t count;                                                              \
    ll_lpush_func_##TYPE LPush;                                                \
    ll_rpush_func_##TYPE RPush;                                                \
    ll_at_func_##TYPE At;                                                      \
  };

#define LL_LPUSH(TYPE)                                                         \
  static inline void ListLPush_##TYPE(LIST_TYPE(TYPE) * ll, TYPE e) {          \
    NODE_TYPE(TYPE) *node =                                                    \
        (NODE_TYPE(TYPE) *)malloc(sizeof(NODE_TYPE(TYPE)));                    \
    if (node == NULL) {                                                        \
      printf("Error allocating memory");                                       \
    }                                                                          \
    node->obj = e;                                                             \
    node->l = NULL;                                                            \
    node->r = ll->head;                                                        \
    if (node->r)                                                               \
      node->r->l = node;                                                       \
    if (ll->tail == NULL)                                                      \
      ll->tail = node;                                                         \
    ll->head = node;                                                           \
    ll->count++;                                                               \
  }

#define LL_RPUSH(TYPE)                                                         \
  static inline void ListRPush_##TYPE(LIST_TYPE(TYPE) * ll, TYPE e) {          \
    NODE_TYPE(TYPE) *node =                                                    \
        (NODE_TYPE(TYPE) *)malloc(sizeof(NODE_TYPE(TYPE)));                    \
    if (node == NULL) {                                                        \
      printf("Error allocating memory");                                       \
    }                                                                          \
    node->obj = e;                                                             \
    node->l = ll->tail;                                                        \
    if (node->l)                                                               \
      node->l->r = node;                                                       \
    node->r = NULL;                                                            \
    if (ll->head == NULL)                                                      \
      ll->head = node;                                                         \
    ll->tail = node;                                                           \
    ll->count++;                                                               \
  }

#define LL_AT(TYPE)                                                            \
  static inline NODE_TYPE(TYPE) *                                              \
      ListAt_##TYPE(LIST_TYPE(TYPE) * ll, size_t index) {                      \
    size_t i = 0;                                                              \
    NODE_TYPE(TYPE) * current_node;                                            \
    if (index < ll->count / 2) {                                               \
      current_node = ll->head;                                                 \
      while (i < index && current_node) {                                      \
        current_node = current_node->r;                                        \
        i++;                                                                   \
      }                                                                        \
      return current_node;                                                     \
    }                                                                          \
    i = ll->count - 1;                                                         \
    current_node = ll->tail;                                                   \
    while (i > index && current_node) {                                        \
      current_node = current_node->l;                                          \
      i--;                                                                     \
    }                                                                          \
    return current_node;                                                       \
  }

#define LL_RPOP(TYPE)
#define LL_LPOP(TYPE)

#define CREATE_LIST(TYPE)                                                      \
  static inline LIST_TYPE(TYPE) CreateList_##TYPE() {                          \
    LIST_TYPE(TYPE) LL;                                                        \
    LL.count = 0;                                                              \
    LL.head = NULL;                                                            \
    LL.tail = NULL;                                                            \
    LL.LPush = ListLPush_##TYPE;                                               \
    LL.RPush = ListRPush_##TYPE;                                               \
    LL.At = ListAt_##TYPE;                                                     \
    return LL;                                                                 \
  }

#define LinkedList(TYPE)                                                       \
  LL_FUNCTION(TYPE)                                                            \
  NODE(TYPE)                                                                   \
  LIST(TYPE)                                                                   \
  LL_LPUSH(TYPE)                                                               \
  LL_RPUSH(TYPE)                                                               \
  LL_AT(TYPE)                                                                  \
  CREATE_LIST(TYPE)

#endif // MUHHAE_LINKED_LIST_H
