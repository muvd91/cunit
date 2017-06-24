#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "cunit.h"

#define NO_REASONS 100
#define INT 1
#define log printf("I got here!\n");

struct utest {
    char *title;
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
char * expected_actual_string(int, void *, void *);


void
print_results(void) {
    struct utest *tmp = head;
    printf("Tests found: %d\n", num_tests);
    if (!num_tests)
        return;
    while (tmp) {
        if (tmp->failed)
            printf("*");
        else
            printf("'");
        tmp = tmp->ptr;
    }
    printf("\n");
    tmp = head;
    while (tmp) {
        if (tmp->failed > 0) {
            printf("Failed test: %s\n", tmp->title);
            print_reasons(tmp->reasons, tmp->failed);
        }
        struct utest *to_free = tmp;
        tmp = tmp->ptr;
        free_utest(to_free);
    }
    printf("\n");
}

void
print_reasons(char **reasons, int number) {
    char **rtmp = reasons;
    for (int i = 0; i < number; i++)
        printf("\t%s\n", *rtmp++);
}

void
test(const char *desc, void (*fn)()) {
    struct utest *new_test;
    if (!num_tests) {
        new_test = head = (struct utest *) malloc(sizeof(struct utest));
        tail = head;
    }
    else {
        new_test = (struct utest *) malloc(sizeof(struct utest));
        tail->ptr = new_test;
        tail = new_test;
    }
    tail->reasons_ptr = tail->reasons;

    new_test->title = (char *)malloc(strlen(desc) + 1);
    strcpy(new_test->title, desc);

    new_test->failed = 0;
    new_test->ptr = NULL;

    (*fn)();
    num_tests++;

    tail = new_test;
}

int
assert_equals_number(const char *reason, long double expected, long double actual) {
    if (expected == actual)
        return 1;
    tail->failed++;
    char *ex_ac = expected_actual_string(INT, &expected, &actual);
    *tail->reasons_ptr = (char *)malloc(strlen(reason) + strlen(ex_ac) + 1);

    strcpy(*tail->reasons_ptr, reason);
    strcat(*tail->reasons_ptr, ex_ac);
    tail->reasons_ptr += 1;
    free(ex_ac);
    return 0;
}

char *
expected_actual_string(int type, void *expected, void *actual) {
    char proto[100];
    char result[100];
    char *r;
    if (type == 1) {
        long double *ex = (long double *)expected;
        long double *ac = (long double *)actual;
        strcpy(proto, " :<expected %Lf but got %Lf>");
        sprintf(result, proto, *ex, *ac);
    }
    if (type == 2) {
        char *ex = (char *)expected;
        char *ac = (char *)actual;
        strcpy(proto, " :<expected \"%s\" but got \"%s\">");
        sprintf(result, proto, ex, ac);
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
    free(ptr->title);
    free(ptr);
}


