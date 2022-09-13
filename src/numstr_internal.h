/**
 * @file numstr_internal.h
 * @author ajheck
 * @brief Internal functions for the numstr library; exposed in a header for testability
 * @version 0.1
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _NUMSTR_INTERNAL_H_
#define _NUMSTR_INTERNAL_H_

#include "numstr.h"
#include "stdbool.h"

#define NSI_RET_ON_TRUE(func, retcode) \
    do                                 \
    {                                  \
        if ((func))                    \
        {                              \
            return (retcode);          \
        }                              \
    } while (0)

#define NSI_RET_ON_FALSE(func, retcode) NSI_RET_ON_TRUE(!(func), (retcode))

#define NSI_RET_ON_ERR(func)         \
    do                               \
    {                                \
        numstr_ret_t v = (func);     \
        if (v != NUMSTR_RET_SUCCESS) \
        {                            \
            return v;                \
        }                            \
    } while (0)

/**
 * @brief Check if a base is supported by the numstr library
 *
 * @param base
 * @return numstr_ret_t
 */
bool nsi_base_is_valid(uint8_t base);

/**
 * @brief Checks if the given numstr has a string buffer which contains at least 1 null terminaotr, and that the string has valid chars for the base
 *
 * @param num pointer to a numstr_t to be checked
 * @return true num contains a valid, null-terminated string for the assigned base.
 * @return false otherwise.
 */
numstr_ret_t nsi_str_is_valid(numstr_t *num);

/**
 * @brief Check if a character digit is valid for a given base
 *
 * @param c digit to be checked
 * @param base check if c is valid for this base
 * @return true if c is a char for a string in the given base.
 * @return false otherwise.
 */
bool nsi_char_is_valid_for_base(char c, uint8_t base);

/**
 * @brief Encode an integer value as a digit character
 *
 * @param value the value to be converted
 * @return char '\0' if the conversion failed, a valid char otherwise
 */
static inline char nsi_value_to_char(int value)
{

    if (value <= 9 && value >= 0)
    {
        return '0' + value;
    }
    else if (value <= 35 && value >= 10)
    {
        /**
         * Formula is 'A' + (value - 10) ->
         * 65 + value + -10 ->
         * 55 + value
         */
        return 55 + value;
    }
    else if (value <= 61 && value >= 36)
    {
        /**
         * Formula is 'a' + (value - 36) ->
         * 97 + value + -36 ->
         * 61 + value ->
         */
        return 61 + value;
    }

    return '\0';
}

/**
 * @brief Get the encoded value of a digit character
 *
 * @param c the char to be converted
 * @return int -1 if an error occured, otherwise the encoded value of c
 */
static inline int nsi_char_to_value(char c)
{

    if (c <= '9' && c >= '0')
    {
        return c - '0';
    }
    else if (c <= 'Z' && c >= 'A')
    {
        /**
         * Formula is c - 'A' + 10 ->
         * c + -65 + 10 ->
         * c - 55
         */
        return c - 55;
    }
    else if (c <= 'z' && c >= 'a')
    {
        /**
         * Formula is c - 'a' + 36 ->
         * c + -97 + 36 ->
         * c - 61
         */
        return c - 61;
    }

    return -1;
}

#endif // #ifndef _NUMSTR_INTERNAL_H_