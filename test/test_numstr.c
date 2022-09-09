#include "minunit.h"

#include "../src/numstr.h"
#include "../src/numstr_utils.h"

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

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(numstr_utils_memcpy_suite);
	MU_RUN_SUITE(numstr_utils_memset_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}