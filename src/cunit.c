#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "cunit.h"

#define NO_REASONS 100

enum TYPE {INT, STRING, BOOLEAN};

struct utest {
    char *description;
    char *reasons[NO_REASONS];
    char **reasons_ptr;
    int failed;
    struct utest *ptr;
};

struct utest *head;
struct utest *tail;
int num_tests = 0;

void print_reasons(char **, int);
void free_utest(struct utest *);
char * expected_actual_string(enum TYPE, void *, void *);
void fail_test_with_reason(const char *, char *);



void
print_results(void) {
    struct utest *tmp = head;
    printf("Tests found: %d\n", num_tests);
    if (!num_tests)
        return;
    while (tmp) {
        if (tmp->failed) {
            printf("✘ %s\n", tmp->description);
            print_reasons(tmp->reasons, tmp->failed);
        }
        else
            printf("✔ %s\n", tmp->description);
        tmp = tmp->ptr;
    }
    printf("\n");
    tmp = head;
    printf("\n");
}

void
print_reasons(char **reasons, int number) {
    char **rtmp = reasons;
    for (int i = 0; i < number; i++)
        printf("    %s\n", *rtmp++);
}

void
test(const char *description, void (*fn)()) {
    if (!num_tests) {
        tail = head = (struct utest *) malloc(sizeof(struct utest));
    }
    else {
        struct utest *new_test = (struct utest *) malloc(sizeof(struct utest));
        tail->ptr = new_test;
        tail = new_test;
        tail->ptr = NULL;
    }
    tail->reasons_ptr = tail->reasons;

    tail->description = (char *)malloc(strlen(description) + 1);
    strcpy(tail->description, description);

    tail->failed = 0;

    (*fn)();
    num_tests++;
}

int
assert_equal_numbers(const char *reason, long double expected, long double actual) {
    if (expected == actual)
        return 0;
    char *ex_ac = expected_actual_string(INT, &expected, &actual);
    fail_test_with_reason(reason, ex_ac);
    free(ex_ac);
    return 1;
}

int
assert_equal_strings(const char *reason, char *expected, char *actual) {
    if (strcmp(expected, actual) == 0)
        return 0;
    char *ex_ac = expected_actual_string(STRING, expected, actual);
    fail_test_with_reason(reason, ex_ac);
    free(ex_ac);
    return 1;
}

int
assert_true(const char *reason, int expr) {
    if (expr)
        return 0;
    int true = 1;
    char *ex_ac = expected_actual_string(BOOLEAN, NULL, NULL);
    fail_test_with_reason(reason, ex_ac);
    free(ex_ac);
    return 1;
}

void
fail_test_with_reason(const char *reason, char *expected_actual) {
    tail->failed++;
    *tail->reasons_ptr = (char *)malloc(strlen(reason) + strlen(expected_actual) + 1);
    strcpy(*tail->reasons_ptr, reason);
    strcat(*tail->reasons_ptr, expected_actual);
    tail->reasons_ptr += 1;
}

char *
expected_actual_string(enum TYPE type, void *expected, void *actual) {
    char proto[100];
    char result[100];
    char *r;
    if (type == INT) {
        long double *ex = (long double *)expected;
        long double *ac = (long double *)actual;
        strcpy(proto, ": expected %.50Lg but got %.50Lg");
        sprintf(result, proto, *ex, *ac);
    }
    else if (type == STRING) {
        char *ex = (char *)expected;
        char *ac = (char *)actual;
        strcpy(proto, ": expected \"%s\" but got \"%s\"");
        sprintf(result, proto, ex, ac);
    }
    else if (type == BOOLEAN) {
        strcpy(result, ": statement expected to be true but was false.");
    }
    r = (char *)malloc(strlen(result) + 1);
    strcpy(r,result);
    return r;
}

void
free_utest(struct utest *ptr) {
    char **t = ptr->reasons;
    for (int i = 0; i < ptr->failed; i++) {
        free(*t++);
    }
    free(ptr->description);
    free(ptr);
}
