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

#define NSI_RET_ON_TRUE(func, retcode) do { if ((func)) { return (retcode); }  } while(0)

#define NSI_RET_ON_FALSE(func, retcode) NSI_RET_ON_TRUE(!(func), (retcode))

#define NSI_RET_ON_ERR(func) do { int nsi_ret_code_as_int = (func); if ( nsi_ret_code_as_int < 0 ) { return nsi_ret_code_as_int; }  } while(0)

/**
 * @brief Set a numstr_t to empty
 * 
 * @param num Pointer to the numstr_t to be set to empty
 */
void nsi_set_empty(numstr_t *num);

/**
 * @brief Append a digit to the end of a numstr_t; equivalent to a left shift by 1 digit and then adding the given digit
 * 
 * @param num Pointer to the numstr_t to be appended to
 * @param digit character to be appended
 * @return numstr_ret_t NUMSTR_RET_SUCCESS on success, a negative NUMSTR_RET_* otherwise 
 */
numstr_ret_t nsi_append_digit(numstr_t *num, char digit);

/**
 * @brief Get how many more digits can be added to the number
 * 
 * @param num Pointer to the numstr_t to be checked
 * @return int the number of free digits left; if negative, the num is in a bad state
 */
int nsi_empty_digit_count(numstr_t *num);

/**
 * @brief Check if a numstr_t is "empty"
 * 
 * @param num numstr_t to be checked
 * @return true if empty
 * @return false otherwise
 */
bool nsi_is_empty(numstr_t *num);

/**
 * @brief Check if a base is supported by the numstr library
 * 
 * @param base 
 * @return true if base is a valid base.
 * @return false otherwise.
 */
bool nsi_base_is_valid(uint8_t base);

/**
 * @brief Checks if the given numstr has a string buffer which contains at least 1 null terminaotr, and that the string has valid chars for the base
 * 
 * @param num pointer to a numstr_t to be checked
 * @return int the number of valid digits in the numstr_t string on success, on failure a negative NUMSTR_RET_* 
 */
int nsi_str_is_valid(numstr_t *num);

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
static inline char nsi_value_to_char(int value) {

    if (value <= 9) {
        if( value >= 0) {
            return '0' + value;
        }
    } else if ( value <= 62 ) {
        /**
         * Formula is 'A' + (value - 10) ->
         * 65 + value + -10 ->
         * 55 + value ->
         * '7' + value
         */
        return '7' + value;
    }
    
    return '\0';    
}

/**
 * @brief Get the encoded value of a digit character
 * 
 * @param c the char to be converted
 * @return int -1 if an error occured, otherwise the encoded value of c
 */
static inline int nsi_char_to_value(char c) {

    if (c <= '9') {
        if( c >='0') {
            return c - '0';
        }
    } else if (c >= 'A') {
        if( c <= 'z') {
            /**
             * Formula is c - 'A' + 10 ->
             * c + -65 + 10 ->
             * c - 55 ->
             * c - '7'
             */
            return c - '7';
        }
    }

    return -1;
}

#endif // #ifndef _NUMSTR_INTERNAL_H_