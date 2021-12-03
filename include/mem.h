#pragma once

#include <stddef.h>

void* aligned_alloc(size_t alignment, size_t size);
void* malloc(size_t __size);
void free(void* __ptr);

inline void* mcopy(void* dest, const void* src, size_t len)
{
  char* d = (char*) dest;
  const char* s = (const char*) src;
  while (len--)
    *d++ = *s++;
  return dest;
}