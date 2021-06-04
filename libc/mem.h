#ifndef LIBC_MEM_H
#define LIBC_MEM_H

#include "../cpu/types.h"

void memcpy(char *dst, char *src,int n);
void *memset(void *s, int c, unsigned int len);

#endif