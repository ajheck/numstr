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
    int retcode;
    retcode = nsi_char_to_value(c);
    return (retcode > -1) && (retcode < base);
}

bool nsi_base_is_valid(uint8_t base)
{
    return (base >= 2 && base <= 62);
}

numstr_ret_t nsi_str_is_valid(numstr_t *num)
{
    int i;

    // First, look for at least 1 null terminator
    for (i = num->str_size - 1;
         i >= 0 && num->str[i] != '\0';
         --i)
        ;

    NSI_RET_ON_TRUE(i < 0, NUMSTR_RET_ERR_STR_MISSING_NULL);

    // There is a null terminator!
    // Start from the front and check that the string contains only valid characters
    for (i = 0; num->str[i] != '\0'; ++i)
    {
        if(!nsi_char_is_valid_for_base(num->str[i], num->base)) {
            return NUMSTR_RET_ERR_INVALID_CHAR_FOR_BASE;
        }
    }

    return i;
}

void nsi_set_empty(numstr_t *num)
{
    num->base = 0;
    num->str[0] = '\0';
    num->str[num->str_size - 1] = '\0';
    num->digit_count = 0;
}

bool nsi_is_empty(numstr_t *num)
{
    return (0 == num->base) && (0 == num->digit_count) && ('\0' == num->str[0]) && ('\0' == num->str[num->str_size - 1]);
}

int nsi_empty_digit_count(numstr_t *num)
{
    int digit_count;
    NSI_RET_ON_ERR(digit_count = numstr_digit_count(num));
    return num->str_size - digit_count - 1;
}

numstr_ret_t nsi_append_digit(numstr_t *num, char digit)
{
    int digit_count;

    NSI_RET_ON_FALSE(nsi_char_is_valid_for_base(digit, num->base), NUMSTR_RET_ERR_INVALID_CHAR_FOR_BASE);

    NSI_RET_ON_FALSE(nsi_empty_digit_count(num) > 0, NUMSTR_RET_ERR_NO_SPACE);

    NSI_RET_ON_ERR(digit_count = numstr_digit_count(num));

    num->str[digit_count] = digit;
    num->str[digit_count + 1] = '\0';
    num->digit_count++;

    return NUMSTR_RET_SUCCESS;
}