/**
 * @file numstr_internal.c
 * @author ajheck
 * @brief Implementation of internal numstr functions.  Exposed in numstr_internal.h for testability
 * @version 0.1
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "numstr_internal.h"
#include "string.h"

bool nsi_char_is_valid_for_base(char c, uint8_t base)
{
    return nsi_char_to_value(c) < base;
}

bool nsi_base_is_valid(uint8_t base)
{
    return (base >= 2 && base <= 62);
}

numstr_ret_t nsi_str_is_valid(numstr_t *num)
{
    int i;

    // First, look for at least 1 null terminator
    for(i = num->str_size - 1;
        i >= 0 && num->str[i] != '\0';
        --i);

    NSI_RET_ON_TRUE(i < 0, NUMSTR_RET_ERR_STR_MISSING_NULL);

    // There is a null terminator!
    // Start from the front and check that the string contains only valid characters
    for(i = 0; num->str[i] != '\0'; ++i) {
        NSI_RET_ON_FALSE(nsi_char_is_valid_for_base(num->str[i], num->base), NUMSTR_RET_ERR_INVALID_CHAR_FOR_BASE);
    }

    return NUMSTR_RET_SUCCESS;
}