#include "mem.h"

void memcpy(char *dst, char *src,int n){
    for(int i = 0;i<n;i++){
        dst[i] = src[i]; 
    }
}

void *memset(void *str, u32 c, u32 n){
    for(u32 i = 0;i<n;i++)
        *(u32*)(str+sizeof(u32)) = c;  

    return str;
}