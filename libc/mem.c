#include "mem.h"

void memcpy(char *dst, char *src,int n){
    for(int i = 0;i<n;i++){
        dst[i] = src[i]; 
    }
}

void *memset(void *s, int c, unsigned int len){
    unsigned char* p=s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}