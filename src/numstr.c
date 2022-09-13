
#include "numstr.h"

#include "numstr_internal.h"

numstr_ret_t numstr_fill_from_str(numstr_t *num, char *str, size_t str_size, uint8_t base)
{
    numstr_ret_t retcode;
    int result;
    if (NULL == num || NULL == str)
    {
        return NUMSTR_RET_ERR_NULL_PTR;
    }

    NSI_RET_ON_FALSE(nsi_base_is_valid(base), NUMSTR_RET_ERR_INVALID_BASE);

    num->base = base;
    num->str = str;
    num->str_size = str_size;

    NSI_RET_ON_ERR(result = nsi_str_is_valid(num));

    num->digit_count = (size_t)result;

    return NUMSTR_RET_SUCCESS;
}

numstr_ret_t numstr_fill_as_empty(numstr_t *num, char *str, size_t str_size)
{
    numstr_ret_t retcode;
    if (NULL == num || NULL == str)
    {
        return NUMSTR_RET_ERR_NULL_PTR;
    }

    num->str = str;
    num->str_size = str_size;

    nsi_set_empty(num);

    return NUMSTR_RET_SUCCESS;
}

numstr_ret_t numstr_divide_int(numstr_t *num, int divisor, numstr_t *result, int *remainder)
{
    int64_t r;
    int i;

    if (NULL == num || NULL == result || NULL == remainder)
    {
        return NUMSTR_RET_ERR_NULL_PTR;
    }

    // configure empty result
    nsi_set_empty(result);
    
    // Divide each digit, and carry the remainder forward to the next digit
    for(i = 0, r = 0; i < numstr_digit_count(num); ++i) {
        int digit_val;
        int new_digit_val;
        
        digit_val = nsi_char_to_value(num->str[i]);
        NSI_RET_ON_TRUE(digit_val < 0, NUMSTR_RET_ERR_INVALID_CHAR);
        r = num->base * r + digit_val;
        new_digit_val = r / divisor;
        r %= divisor;

        // Add new digits as needed
        if(new_digit_val > 0 || !nsi_is_empty(result)) {
            char new_digit;
            result->base = num->base;
            new_digit = nsi_value_to_char(new_digit_val);
            NSI_RET_ON_TRUE( '\0' == new_digit, NUMSTR_RET_ERR_INVALID_CHAR);
            NSI_RET_ON_ERR(nsi_append_digit(result, new_digit));
        }
    }

    if(nsi_is_empty(result)) {
        NSI_RET_ON_ERR(nsi_append_digit(result, '0'));
    }

    *remainder = (int)r;
    return NUMSTR_RET_SUCCESS;
}

int numstr_digit_count(numstr_t *num)
{
    if (NULL == num)
    {
        return NUMSTR_RET_ERR_NULL_PTR;
    }

    return num->digit_count;
}