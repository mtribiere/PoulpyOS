#include "string.h"
#include "../drivers/screen.h"

int strcmp( const char * first, const char * second ){
    
    int isValid = 1;

    while(*first && *second && isValid)
        isValid = isValid && ((*(first++)) == (*(second++)));
    
    return (isValid && !(*first) && !(*second));

}