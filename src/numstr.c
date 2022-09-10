
#include "numstr.h"

#include "numstr_internal.h"

#define RET_ON_FALSE(func, err) do { if (!(func)) { return (err); }  } while(0)

#define RET_ON_ERR(func) do { numstr_ret_t v = (func); if ( v != NUMSTR_RET_SUCCESS ) { return v; }  } while(0)

numstr_ret_t numstr_fill_from_str(numstr_t *num, char* str, size_t str_size, uint8_t base) {
    numstr_ret_t retcode;
    if(NULL == num || NULL == str) {
        return NUMSTR_RET_ERR_NULL_PTR;
    }

    RET_ON_FALSE(nsi_base_is_valid(base), NUMSTR_RET_ERR_INVALID_BASE);

    num->base = base;
    num->str = str;
    num->str_size = str_size;

    RET_ON_ERR(nsi_str_is_valid(num));

    return NUMSTR_RET_SUCCESS;
}