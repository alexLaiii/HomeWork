// test_strrmlast.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "a5.h"   // must declare: void strrmlast(char *s, char c);

// helper: run one test with expected result
static void run_test(const char *label, const char *initial, char c, const char *expected) {
    // make a modifiable copy on the stack
    char buf[256];
    size_t len = strlen(initial);
    assert(len < sizeof(buf)); // just to be safe

    strcpy(buf, initial);

    printf("=== %s ===\n", label);
    printf("before: \"%s\" (remove '%c')\n", buf, c);

    strrmlast(buf, c);

    printf("after : \"%s\"\n", buf);
    printf("expect: \"%s\"\n\n", expected);

    assert(strcmp(buf, expected) == 0);
}

// test: example from the spec
static void test_spec_example(void) {
    char str[] = "hello";
    printf("=== spec example ===\n");
    printf("before: \"%s\" (remove 'l')\n", str);

    strrmlast(str, 'l');

    printf("after : \"%s\"\n\n", str);
    assert(strcmp(str, "helo") == 0);
}

// test: character not found -> string unchanged
static void test_not_found(void) {
    run_test("not found", "banana", 'x', "banana");
}

// test: remove last occurrence in middle
static void test_middle(void) {
    run_test("last in middle", "abracadabra", 'a', "abracadabr");
}

// test: remove last character
static void test_last_char(void) {
    run_test("last char", "abcdx", 'x', "abcd");
}

// test: remove first character (when it is also last occurrence)
static void test_first_only(void) {
    run_test("first only", "xyz", 'x', "yz");
}

// test: multiple same chars -> only last removed
static void test_multiple_same(void) {
    run_test("multiple same", "aaaaa", 'a', "aaaa");
}

// test: length 1 string, char matches
static void test_len1_match(void) {
    run_test("len 1 match", "z", 'z', "");
}

// test: length 1 string, char does not match
static void test_len1_nomatch(void) {
    run_test("len 1 no match", "z", 'x', "z");
}

// test: empty string (should stay empty)
static void test_empty(void) {
    char s[1];
    s[0] = '\0';

    printf("=== empty string ===\n");
    printf("before: \"%s\" (remove 'a')\n", s);

    strrmlast(s, 'a');

    printf("after : \"%s\"\n\n", s);
    assert(strcmp(s, "") == 0);
}

// test: whitespace and punctuation
static void test_spaces_punct(void) {
    run_test("spaces/punct", "a b c d a!", 'a', "a b c d !");
}

// test: multiple calls on same string
static void test_multiple_calls(void) {
    char s[256];
    strcpy(s, "mississippi");

    printf("=== multiple calls (mississippi, remove 's') ===\n");
    printf("start: \"%s\"\n", s);

    strrmlast(s, 's');  // mississippi -> missisippi
    printf("step1: \"%s\"\n", s);
    assert(strcmp(s, "missisippi") == 0);

    strrmlast(s, 's');  // missisippi -> missiippi
    printf("step2: \"%s\"\n", s);
    assert(strcmp(s, "missiippi") == 0);

    strrmlast(s, 's');  // missiippi -> misiippi
    printf("step3: \"%s\"\n", s);
    assert(strcmp(s, "misiippi") == 0);

    strrmlast(s, 's');  // misiippi -> miiippi
    printf("step4: \"%s\"\n", s);
    assert(strcmp(s, "miiippi") == 0);

    // no more 's' — next call should not change it
    char before[256];
    strcpy(before, s);
    strrmlast(s, 's');
    assert(strcmp(s, before) == 0);
}


int main(void) {
    test_spec_example();
    test_not_found();
    test_middle();
    test_last_char();
    test_first_only();
    test_multiple_same();
    test_len1_match();
    test_len1_nomatch();
    test_empty();
    test_spaces_punct();
    test_multiple_calls();

    printf("All tests passed.\n");
    return 0;
}
