#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "a5.h"   // must declare: char *strrepeat(const char *s, size_t n);

struct TestCase {
    const char *s;
    size_t n;
    const char *expected;
};

int main(void) {
    struct TestCase tests[] = {
        { "",               0,  "" },
        { "",               1,  "" },
        { "",               5,  "" },
        { "a",              0,  "" },
        { "a",              1,  "a" },
        { "a",              5,  "aaaaa" },
        { "ab",             1,  "ab" },
        { "ab",             4,  "abababab" },
        { "hello",          3,  "hellohellohello" },
        { "xyz",            2,  "xyzxyz" },
        { "Hi ",            3,  "Hi Hi Hi " },
        { "  x",            3,  "  x  x  x" },
        { "!",              10, "!!!!!!!!!!" },
        { "A\n",            3,  "A\nA\nA\n" },
        { "0123456789",     2,  "01234567890123456789" },
        { "abc",            0,  "" },
    };

    int n_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n_tests; i++) {
        const char *s = tests[i].s;
        size_t n = tests[i].n;
        const char *expected = tests[i].expected;

        char *rep = strrepeat(s, n);
        if (rep == NULL) {
            printf("Test %2d: strrepeat(\"%s\", %zu) -> NULL (allocation failed?) ❌\n",
                   i + 1, s, n);
            continue;
        }

        int ok = strcmp(rep, expected) == 0;

        printf("Test %2d: strrepeat(\"%s\", %zu)\n", i + 1, s, n);
        printf("  Expected: \"%s\"\n", expected);
        printf("  Got     : \"%s\"  %s\n\n", rep, ok ? "✅" : "❌");

        free(rep);  // important: function returns newly allocated memory
    }

    return 0;
}
