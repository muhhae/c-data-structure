#ifndef MUHHAE_LINKED_LIST_H
#define MUHHAE_LINKED_LIST_H

#include "util.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_TYPE(TYPE) node_##TYPE##_t
#define LIST_TYPE(TYPE) list_##TYPE##_t

#define LL_PROTOTYPE(TYPE)                                                     \
  struct NODE_TYPE(TYPE);                                                      \
  struct LIST_TYPE(TYPE);                                                      \
  typedef struct NODE_TYPE(TYPE) NODE_TYPE(TYPE);                              \
  typedef struct LIST_TYPE(TYPE) LIST_TYPE(TYPE);                              \
  typedef TYPE *(*ll_lpush_func_##TYPE)(LIST_TYPE(TYPE) *, TYPE);              \
  typedef TYPE *(*ll_rpush_func_##TYPE)(LIST_TYPE(TYPE) *, TYPE);              \
  typedef void (*ll_destroy_func_##TYPE)(LIST_TYPE(TYPE) *);                   \
  typedef TYPE *(*ll_at_func_##TYPE)(LIST_TYPE(TYPE) *, size_t);               \
  typedef TYPE (*ll_rpop_func_##TYPE)(LIST_TYPE(TYPE) *);                      \
  typedef TYPE (*ll_lpop_func_##TYPE)(LIST_TYPE(TYPE) *);

#define NODE(TYPE)                                                             \
  struct NODE_TYPE(TYPE) {                                                     \
    TYPE value;                                                                \
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
    ll_lpop_func_##TYPE LPop;                                                  \
    ll_rpop_func_##TYPE RPop;                                                  \
    ll_destroy_func_##TYPE Destroy;                                            \
    free_func _customFree;                                                     \
  };

#define LL_LPUSH(TYPE)                                                         \
  static TYPE *ListLPush_##TYPE(LIST_TYPE(TYPE) * ll, TYPE e) {                \
    NODE_TYPE(TYPE) *node =                                                    \
        (NODE_TYPE(TYPE) *)malloc(sizeof(NODE_TYPE(TYPE)));                    \
    if (node == NULL) {                                                        \
      fprintf(stderr, "Memory allocation failed\n");                           \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
    node->value = e;                                                           \
    node->l = NULL;                                                            \
    node->r = ll->head;                                                        \
    if (node->r)                                                               \
      node->r->l = node;                                                       \
    if (ll->tail == NULL)                                                      \
      ll->tail = node;                                                         \
    ll->head = node;                                                           \
    ll->count++;                                                               \
    return &ll->head->value;                                                   \
  }

#define LL_RPUSH(TYPE)                                                         \
  static TYPE *ListRPush_##TYPE(LIST_TYPE(TYPE) * ll, TYPE e) {                \
    NODE_TYPE(TYPE) *node =                                                    \
        (NODE_TYPE(TYPE) *)malloc(sizeof(NODE_TYPE(TYPE)));                    \
    if (node == NULL) {                                                        \
      fprintf(stderr, "Memory allocation failed\n");                           \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
    node->value = e;                                                           \
    node->l = ll->tail;                                                        \
    if (node->l)                                                               \
      node->l->r = node;                                                       \
    node->r = NULL;                                                            \
    if (ll->head == NULL)                                                      \
      ll->head = node;                                                         \
    ll->tail = node;                                                           \
    ll->count++;                                                               \
    return &ll->tail->value;                                                   \
  }

#define LL_NODE_AT(TYPE)                                                       \
  static NODE_TYPE(TYPE) *                                                     \
      ListNodeAt_##TYPE(LIST_TYPE(TYPE) * ll, size_t index) {                  \
    if (index > ll->count - 1)                                                 \
      return NULL;                                                             \
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

#define LL_AT(TYPE)                                                            \
  static inline TYPE *ListAt_##TYPE(LIST_TYPE(TYPE) * ll, size_t index) {      \
    NODE_TYPE(TYPE) *node = ListNodeAt_##TYPE(ll, index);                      \
    return node ? &node->value : NULL;                                         \
  }

#define LL_RPOP(TYPE)                                                          \
  static TYPE ListRPop_##TYPE(LIST_TYPE(TYPE) * ll) {                          \
    if (!ll->tail)                                                             \
      return (TYPE){0};                                                        \
    TYPE copy_tmp = ll->tail->value;                                           \
    NODE_TYPE(TYPE) *new_tail = ll->tail->l;                                   \
    free(ll->tail);                                                            \
    ll->tail = new_tail;                                                       \
    if (ll->tail)                                                              \
      ll->tail->r = NULL;                                                      \
    else                                                                       \
      ll->head = NULL;                                                         \
    ll->count--;                                                               \
    return copy_tmp;                                                           \
  }

#define LL_LPOP(TYPE)                                                          \
  static TYPE ListLPop_##TYPE(LIST_TYPE(TYPE) * ll) {                          \
    if (!ll->head)                                                             \
      return (TYPE){0};                                                        \
    TYPE copy_tmp = ll->head->value;                                           \
    NODE_TYPE(TYPE) *new_head = ll->head->r;                                   \
    free(ll->head);                                                            \
    ll->head = new_head;                                                       \
    if (ll->head)                                                              \
      ll->head->l = NULL;                                                      \
    else                                                                       \
      ll->tail = NULL;                                                         \
    ll->count--;                                                               \
    return copy_tmp;                                                           \
  }

#define LL_INSERT(TYPE)                                                        \
  static TYPE *ListInsertAt_##TYPE(LIST_TYPE(TYPE) * ll, size_t index,         \
                                   TYPE value) {                               \
    if (index == 0) {                                                          \
      ll->LPush(value);                                                        \
      return;                                                                  \
    }                                                                          \
    if (index >= ll->count) {                                                  \
      ll->RPush(value);                                                        \
      return;                                                                  \
    }                                                                          \
    NODE_TYPE(TYPE) *node = ListNodeAt_##TYPE(ll, index);                      \
    NODE_TYPE(TYPE) *new_node =                                                \
        (NODE_TYPE(TYPE) *)malloc(sizeof(NODE_TYPE(TYPE)));                    \
    new_node->r = node;                                                        \
    new_node->l = node->l;                                                     \
    node->l = new_node;                                                        \
    return &new_node->value;                                                   \
  }

#define LL_REMOVE(TYPE)                                                        \
  static void ListRemoveAt_##TYPE(LIST_TYPE(TYPE) * ll, size_t index) {        \
    if (index == 0) {                                                          \
      TYPE tmp = ll->LPop();                                                   \
      myFree(&tmp, ll->_customFree);                                           \
      return;                                                                  \
    }                                                                          \
    if (index == ll->count - 1) {                                              \
      TYPE tmp = ll->RPop();                                                   \
      myFree(&tmp, ll->_customFree);                                           \
      return;                                                                  \
    }                                                                          \
    if (index >= ll->count) {                                                  \
      return;                                                                  \
    }                                                                          \
    NODE_TYPE(TYPE) *node = ListNodeAt_##TYPE(ll, index);                      \
  }

#define CREATE_LIST(TYPE, CUSTOM_FREE_FUNC)                                    \
  static LIST_TYPE(TYPE) CreateList_##TYPE() {                                 \
    LIST_TYPE(TYPE) LL;                                                        \
    LL.count = 0;                                                              \
    LL.head = NULL;                                                            \
    LL.tail = NULL;                                                            \
    LL.LPush = ListLPush_##TYPE;                                               \
    LL.RPush = ListRPush_##TYPE;                                               \
    LL.At = ListAt_##TYPE;                                                     \
    LL.RPop = ListRPop_##TYPE;                                                 \
    LL.LPop = ListLPop_##TYPE;                                                 \
    LL.Destroy = ListDestroy_##TYPE;                                           \
    LL._customFree = CUSTOM_FREE_FUNC;                                         \
    return LL;                                                                 \
  }

#define LL_DESTROY(TYPE)                                                       \
  /*Destroy the list entirely, clean up the memory with _customFree if not     \
   * null */                                                                   \
  static inline void ListDestroy_##TYPE(LIST_TYPE(TYPE) * ll) {                \
    while (ll->head) {                                                         \
      TYPE e = ll->LPop(ll);                                                   \
      if (ll->_customFree)                                                     \
        myFree(&e, ll->_customFree);                                           \
    }                                                                          \
  }

#define DefineLinkedList(TYPE, CUSTOM_FREE_FUNC)                               \
  LL_PROTOTYPE(TYPE)                                                           \
  NODE(TYPE)                                                                   \
  LIST(TYPE)                                                                   \
  LL_LPUSH(TYPE)                                                               \
  LL_RPUSH(TYPE)                                                               \
  LL_RPOP(TYPE)                                                                \
  LL_LPOP(TYPE)                                                                \
  LL_NODE_AT(TYPE)                                                             \
  LL_AT(TYPE)                                                                  \
  LL_DESTROY(TYPE)                                                             \
  CREATE_LIST(TYPE, CUSTOM_FREE_FUNC)

#endif // MUHHAE_LINKED_LIST_H
