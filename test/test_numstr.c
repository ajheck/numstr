#include "minunit.h"

#include "../src/numstr_utils.h"
#include "../src/numstr_internal.h"

/************************* BEGIN numster_utils.c TESTS *************************/

MU_TEST(numstr_utils_memcpy_copies_as_expected)
{
    char source[] = "hello";
    char dest[] = "12345";
    char *returnedPointer = numstr_utils_memcpy(dest, source, strlen(source));
    mu_assert(dest == returnedPointer, "returned pointer did not equal passed pointer");
    mu_assert_string_eq(source, dest);
}

MU_TEST_SUITE(numstr_utils_memcpy_suite)
{
    MU_RUN_TEST(numstr_utils_memcpy_copies_as_expected);
}

MU_TEST(numstr_utils_memset_sets_as_expected)
{
    char buffer[] = "hello";
    char *returnedPointer = numstr_utils_memset(buffer, 'a', strlen(buffer));
    mu_assert(buffer == returnedPointer, "returned pointer did not equal passed pointer");
    mu_assert_string_eq(buffer, "aaaaa");
}

MU_TEST_SUITE(numstr_utils_memset_suite)
{
    MU_RUN_TEST(numstr_utils_memset_sets_as_expected);
}

MU_TEST(numstr_utils_malloc_and_numstr_utils_free_work_nominally)
{
    void *ptr = numstr_utils_malloc(10);
    mu_assert(NULL != ptr, "returned null pointer!");
    numstr_utils_free(ptr);
}

MU_TEST_SUITE(numstr_utils_malloc_and_numstr_utils_free_suite)
{
    MU_RUN_TEST(numstr_utils_malloc_and_numstr_utils_free_work_nominally);
}

/************************* END numster_utils.c TESTS *************************/

/************************* BEGIN numster_internal.c TESTS *************************/

/************************* END numster_internal.c TESTS *************************/

MU_TEST(nsi_char_to_value_test_all_byte_values)
{
    /**
     * Expected mapping is as follows
     * '0' <= c <= '9' -> 0 to 9
     * 'A' <= c <= 'z' -> 10 to 62
     * else -1
     */
    for (int i = 0; i < 256; ++i)
    {
        char c = (char)(i & 0xFF);
        int expectedValue;
        if (c >= '0' && c <= '9')
        {
            expectedValue = c - '0';
        }
        else if (c >= 'A' && c <= 'Z')
        {
            expectedValue = c - 'A' + 10;
        }
        else if (c >= 'a' && c <= 'z')
        {
            expectedValue = c - 'a' + 36;
        }
        else
        {
            expectedValue = -1;
        }
        mu_assert_int_eq(expectedValue, nsi_char_to_value(c));
    }
}

MU_TEST(nsi_value_to_char_test_all_int_values)
{
    /**
     * Expected mapping is as follows
     * 0 <= i <= 9 -> '0' to '9''
     * 10 <= i <= 62 -> 'A' to 'z'
     * else -1
     */
    // start at -1 and go to 256 to get values outside uint8_t range
    for (int i = -1; i < 257; ++i)
    {
        char expectedChar;
        if (i >= 0 && i <= 9)
        {
            expectedChar = i + '0';
        }
        else if (i >= 10 && i <= 35)
        {
            expectedChar = i + 'A' - 10;
        }
        else if (i >= 36 && i <= 31)
        {
            expectedChar = i + 'a' - 36;
        }
        mu_assert_int_eq(expectedChar, nsi_value_to_char(i));
    }
}

MU_TEST_SUITE(nsi_char_value_conversion_suite)
{
    MU_RUN_TEST(nsi_char_to_value_test_all_byte_values);
    MU_RUN_TEST(nsi_value_to_char_test_all_int_values);
}

/************************* BEGIN numstr.c TESTS *************************/

MU_TEST(numstr_fill_from_str_works_nominally)
{
    char *hexString = "FEEDF00D";
    uint8_t base = 16;
    size_t strSize = strlen(hexString) + 1;
    numstr_t testNum;

    mu_assert(NUMSTR_RET_SUCCESS == numstr_fill_from_str(&testNum, hexString, strSize, base), "Unexpected err when filling numstr from string");
    mu_assert_int_eq(base, testNum.base);
    mu_assert_int_eq(strSize, testNum.str_size);
    mu_assert(testNum.str == hexString, "Failed to set numstr_t string as expected");
}

MU_TEST(numstr_fill_from_str_fails_on_null_ptrs) {
    char *hexString = "FEEDF00D";
    uint8_t base = 16;
    size_t strSize = strlen(hexString) + 1;
    numstr_t testNum;

    // Test failure when no string is provided
    mu_assert(NUMSTR_RET_ERR_NULL_PTR == numstr_fill_from_str(&testNum, NULL, strSize, base), "Unexpected err when numstr from null string pointer");

    // Test failure when no *numstr_t is provided
    mu_assert(NUMSTR_RET_ERR_NULL_PTR == numstr_fill_from_str(NULL, hexString, strSize, base), "Unexpected err when attempting to fill null numstr pointer");
}

MU_TEST(numstr_fill_from_str_fails_on_invalid_params) {
    char *hexString = "FEEDF00D";
    uint8_t base = 16;
    size_t strSize = strlen(hexString) + 1;
    numstr_t testNum;

    // Test failure when no null character is provided in the string buffer
    mu_assert(NUMSTR_RET_ERR_STR_MISSING_NULL == numstr_fill_from_str(&testNum, hexString, strSize - 2, base), "Unexpected err when filling numstr from string missing '\\0' terminator");

    // Test failure when invalid char is present for a given base
    base = 15;
    mu_assert(NUMSTR_RET_ERR_INVALID_CHAR_FOR_BASE == numstr_fill_from_str(&testNum, hexString, strSize, base), "Unexpected err when filling numstr from string with invalid chars");

    
    // Test failure when invalid base is passed in
    base = 123;
    mu_assert(NUMSTR_RET_ERR_INVALID_BASE == numstr_fill_from_str(&testNum, hexString, strSize, base), "Unexpected err when using invalid base");
}

MU_TEST_SUITE(numstr_fill_from_str_suite)
{
    MU_RUN_TEST(numstr_fill_from_str_works_nominally);
    MU_RUN_TEST(numstr_fill_from_str_fails_on_null_ptrs);
    MU_RUN_TEST(numstr_fill_from_str_fails_on_invalid_params);
}

MU_TEST(numstr_fill_as_empty_works_nominally) {
    char buff[4];
    memset(buff, 'x', sizeof(buff));
    char expectedBuff[4] = { '\0', 'x', 'x', '\0' };
    size_t strSize = sizeof(buff);
    numstr_t testNum;

    mu_assert(NUMSTR_RET_SUCCESS == numstr_fill_as_empty(&testNum, buff, strSize), "Unexpected err when filling numstr as empty");
    mu_assert_int_eq(0, testNum.base);
    mu_assert_int_eq(strSize, testNum.str_size);
    mu_assert(testNum.str == buff, "Failed to set numstr_t string as expected");
    mu_assert_mem_eq(expectedBuff, testNum.str, sizeof(expectedBuff));
}

MU_TEST(numstr_fill_as_empty_fails_on_null_ptrs) {
    char buff[4];
    size_t strSize = sizeof(buff);
    numstr_t testNum;

    mu_assert(NUMSTR_RET_ERR_NULL_PTR == numstr_fill_as_empty(NULL, buff, strSize), "Unexpected err when passing NULL numstr ptr");
    mu_assert(NUMSTR_RET_ERR_NULL_PTR == numstr_fill_as_empty(&testNum, NULL, strSize), "Unexpected err when passing NULL buffer ptr");
}

MU_TEST_SUITE(numstr_fill_as_empty_suite)
{
    MU_RUN_TEST(numstr_fill_as_empty_works_nominally);
    MU_RUN_TEST(numstr_fill_as_empty_fails_on_null_ptrs);
}

/************************* END numstr.c TESTS *************************/

int main(int argc, char *argv[])
{
    // numster_utils.c tests
    MU_RUN_SUITE(numstr_utils_memcpy_suite);
    MU_RUN_SUITE(numstr_utils_memset_suite);
    MU_RUN_SUITE(numstr_utils_malloc_and_numstr_utils_free_suite);

    // numster_internal.c tests
    MU_RUN_SUITE(nsi_char_value_conversion_suite);

    // numstr.c tests
    MU_RUN_SUITE(numstr_fill_from_str_suite);
    MU_RUN_SUITE(numstr_fill_as_empty_suite);

    MU_REPORT();
    return MU_EXIT_CODE;
}