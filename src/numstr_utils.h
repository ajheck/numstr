/**
 * @file numstr_utils.h
 * @author ajheck
 * @brief Utility functions for the numstr library
 * @version 0.1
 * @date 2022-09-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _NUMSTR_UTILS_H_
#define _NUMSTR_UTILS_H_

#include "stdint.h"
#include "numstr.h"

/**
 * @brief If set to NUMSTR_FEATURE_ENABLE, calls to numstr_utils_* will pass the parameters to the string.h and stdlib.h version of the function
 * 
 */
#define NUMSTR_UTILS_USE_STDLIB (NUMSTR_FEATURE_ENABLE)

/**
 * @brief Copy data from one location to another
 * 
 * @param destination pointer to memory where data should be copied to
 * @param source pointer to memory where data should be copied from
 * @param num number of bytes to be copied from source to destination
 * @return void* destination is returned
 */
void * numstr_utils_memcpy(void *destination, const void *source, size_t num);

/**
 * @brief Sets the first num bytes of the block of memory pointed to by ptr to the specified value (interpreted as an unsigned char)
 * 
 * @param ptr Pointer to the block of memory to fill
 * @param value Value to be set. The value is passed as an int, but the function fills the block of memory using the unsigned char conversion of this value
 * @param num Number of bytes to be set to the value
 * @return void* ptr is returned
 */
void * numstr_utils_memset(void *ptr, int value, size_t num);

#endif /* #ifndef _NUMSTR_UTILS_H_ */