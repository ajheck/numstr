#include "minunit.h"

#include "../src/numstr_utils.h"
#include "../src/numstr_internal.h"

/************************* BEGIN numster_utils.c TESTS *************************/

MU_TEST(numstr_utils_memcpy_copies_as_expected) {
    char source[] = "hello";
    char dest[] = "12345";
    char *returnedPointer = numstr_utils_memcpy(dest, source, strlen(source));
    mu_assert(dest == returnedPointer, "returned pointer did not equal passed pointer");
    mu_assert_string_eq(source, dest);
}

MU_TEST_SUITE(numstr_utils_memcpy_suite) {
	MU_RUN_TEST(numstr_utils_memcpy_copies_as_expected);
}

MU_TEST(numstr_utils_memset_sets_as_expected) {
    char buffer[] = "hello";
    char *returnedPointer = numstr_utils_memset(buffer, 'a', strlen(buffer));
    mu_assert(buffer == returnedPointer, "returned pointer did not equal passed pointer");
    mu_assert_string_eq(buffer, "aaaaa");

}

MU_TEST_SUITE(numstr_utils_memset_suite) {
	MU_RUN_TEST(numstr_utils_memset_sets_as_expected);
}

MU_TEST(numstr_utils_malloc_and_numstr_utils_free_work_nominally) {
    void *ptr = numstr_utils_malloc(10);
    mu_assert(NULL != ptr, "returned null pointer!");
    numstr_utils_free(ptr);
}

MU_TEST_SUITE(numstr_utils_malloc_and_numstr_utils_free_suite) {
	MU_RUN_TEST(numstr_utils_malloc_and_numstr_utils_free_work_nominally);
}


/************************* END numster_utils.c TESTS *************************/


/************************* BEGIN numster_internal.c TESTS *************************/


/************************* END numster_internal.c TESTS *************************/

MU_TEST(nsi_char_to_value_test_all_byte_values) {
    /**
     * Expected mapping is as follows
     * '0' <= c <= '9' -> 0 to 9
     * 'A' <= c <= 'z' -> 10 to 62
     * else -1
     */
    for(int i = 0; i < 256; ++i) {
        char c = (char)(i & 0xFF);
        int expectedValue;
        if( c >= '0' && c <='9' ) {
            expectedValue = c - '0';
        } else if ( c >= 'A' && c <= 'z' ) {
            expectedValue = c - 'A' + 10;
        } else {
            expectedValue = -1;
        }
        mu_assert_int_eq(expectedValue, nsi_char_to_value(c));
    }
}

MU_TEST(nsi_value_to_char_test_all_int_values) {
    /**
     * Expected mapping is as follows
     * 0 <= i <= 9 -> '0' to '9''
     * 10 <= i <= 62 -> 'A' to 'z'
     * else -1
     */
    // start at -1 and go to 256 to get values outside uint8_t range
    for(int i = -1; i < 257; ++i) {
        char expectedChar;
        if( i >= 0 && i <= 9 ) {
            expectedChar = i + '0';
        } else if ( i >= 10 && i <= 62 ) {
            expectedChar = i + 'A' - 10;
        } else {
            expectedChar = '\0';
        }
        mu_assert_int_eq(expectedChar, nsi_value_to_char(i));
    }
}

MU_TEST_SUITE(nsi_char_value_conversion_suite) {
    MU_RUN_TEST(nsi_char_to_value_test_all_byte_values);
    MU_RUN_TEST(nsi_value_to_char_test_all_int_values);
}

/************************* BEGIN numstr.c TESTS *************************/



/************************* END numstr.c TESTS *************************/

int main(int argc, char *argv[]) {
    // numster_utils.c tests
	MU_RUN_SUITE(numstr_utils_memcpy_suite);
	MU_RUN_SUITE(numstr_utils_memset_suite);
	MU_RUN_SUITE(numstr_utils_malloc_and_numstr_utils_free_suite);

    // numster_internal.c tests
	MU_RUN_SUITE(nsi_char_value_conversion_suite);

    // numstr.c tests
    
	MU_REPORT();
	return MU_EXIT_CODE;
}