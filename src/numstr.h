/**
 * @file numstr.h
 * @author ajheck
 * @brief numstr library containing functions for numeric string math
 * @version 0.1
 * @date 2022-09-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _NUMSTR_H_
#define _NUMSTR_H_

#include "stdint.h"

#define NUMSTR_FEATURE_ENABLE (1)
#define NUMSTR_FEATURE_DISABLE (2)

/**
 * @brief Return codes for numstr functions.  Negatvie values indicate the function failed.
 * 
 */
typedef enum {
    NUMSTR_RET_SUCCESS = 0,
    NUMSTR_RET_ERR_NULL_PTR = -1,
    NUMSTR_RET_ERR_INVALID_BASE = -2,
    NUMSTR_RET_ERR_INVALID_CHAR_FOR_BASE = -3,
    NUMSTR_RET_ERR_STR_MISSING_NULL = -4,
} numstr_ret_t;

/**
 * @brief A numeric string
 * 
 */
typedef struct{
    uint8_t base;
    char *str;
    size_t str_size;
} numstr_t;

/**
 * @brief Fill out a numstr_t based on an existing numeric string
 * 
 * @param num A pointer to the struct to be filled out
 * @param str Pointer to an  numeric string of size str_len; note that this string is modified by the numstr library
 * @param str_size The length of the BUFFER (not the string str) which str is located in
 * @param base The base of the number represented by str
 * @return numstr_ret_t NUMSTR_RET_SUCCESS on success, a negative NUMSTR_RET_* otherwise
 */
numstr_ret_t numstr_fill_from_str(numstr_t *num, char* str, size_t str_size, uint8_t base);

#endif /* #ifndef _NUMSTR_H_ */