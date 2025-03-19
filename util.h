#ifndef MUHHAE_UTIL_H
#define MUHHAE_UTIL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*free_func)(void *);

/**
 * Workaround so that _customFree could accept both pointer and normal
 * value
 */
static inline void myFree(void *ptr, free_func custom_free) {
  if (custom_free == NULL) {
    fprintf(stderr,
            "custom_free need to be defined, if not, then you shouldn't "
            "call myFree()\n");
    exit(EXIT_FAILURE);
  }
  custom_free(*(void **)ptr);
}

#endif // MUHHAE_UTIL_H
