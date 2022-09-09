/**
 * @file numstr_utils.c
 * @author ajheck
 * @brief Implementation of numstr library
 * @version 0.1
 * @date 2022-09-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "numstr_utils.h"

#if  NUMSTR_FEATURE_ENABLE == NUMSTR_UTILS_USE_STDLIB
#include "string.h"
#include "stdlib.h"
#endif

void *numstr_utils_memcpy(void *destination, const void *source, size_t num) {
#if  NUMSTR_FEATURE_ENABLE == NUMSTR_UTILS_USE_STDLIB
    return memcpy(destination, source, num);
#else
    // Edit as desired
    int i;
    for(i = 0; i < num; ++i) {
        ((uint8_t *)destination)[i] = ((uint8_t *)source)[i];
    }
    return destination;
#endif
}

void * numstr_utils_memset(void *ptr, int value, size_t num) {
#if  NUMSTR_FEATURE_ENABLE == NUMSTR_UTILS_USE_STDLIB
    return memset(ptr, value, num);
#else
    // Edit as desired
    int i;
    unsigned char b;
    for(i = 0, b = value; i < num; ++i) {
        ((uint8_t *)ptr)[i] = b;
    }    
    return ptr;
#endif
}

void * numstr_utils_malloc(size_t size) {
#if  NUMSTR_FEATURE_ENABLE == NUMSTR_UTILS_USE_STDLIB
    return malloc(size);
#else
#error "No default malloc() implementation is provided by numstr; please implement one"
#endif
}

void numstr_utils_free(void *ptr) {
#if  NUMSTR_FEATURE_ENABLE == NUMSTR_UTILS_USE_STDLIB
    free(ptr);
#else
#error "No default free() implementation is provided by numstr; please implement one"
#endif
}