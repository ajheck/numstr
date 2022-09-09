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

/**
 * @brief Copy data from one location to another
 * 
 * @param destination 
 * @param source 
 * @param num 
 */
void *numstr_utils_memcpy(void *destination, const void *source, size_t num) {
    // Edit as desired
    int i;
    for(i = 0; i < num; ++i) {
        ((uint8_t *)destination)[i] = ((uint8_t *)source)[i];
    }
    return destination;
}