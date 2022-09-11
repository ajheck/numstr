
#include "numstr.h"

#include "numstr_internal.h"


numstr_ret_t numstr_fill_from_str(numstr_t *num, char* str, size_t str_size, uint8_t base) {
    numstr_ret_t retcode;
    if(NULL == num || NULL == str) {
        return NUMSTR_RET_ERR_NULL_PTR;
    }

    NSI_RET_ON_FALSE(nsi_base_is_valid(base), NUMSTR_RET_ERR_INVALID_BASE);

    num->base = base;
    num->str = str;
    num->str_size = str_size;

    NSI_RET_ON_ERR(nsi_str_is_valid(num));

    return NUMSTR_RET_SUCCESS;
}

numstr_ret_t numstr_fill_as_empty(numstr_t *num, char *str, size_t str_size) {
    numstr_ret_t retcode;
    if(NULL == num || NULL == str) {
        return NUMSTR_RET_ERR_NULL_PTR;
    }
    
    num->base = 0;
    num->str = str;
    num->str_size = str_size;

    // make the first and last char null
    num->str[0] = '\0';
    num->str[str_size - 1] = '\0';

    return NUMSTR_RET_SUCCESS;
}