#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "cunit.h"

#define NO_REASONS 10
#define INT 1
#define log printf("I got here!\n");

struct utest {
    char *title;
    char *reasons[NO_REASONS];
    int failed;
    struct utest *ptr;
} dummy;

void print_reasons(char **, int);
void free_utest(struct utest *);
char * expected_actual_string(int, void *, void *);

int num_tests = 0;
char **reasons_ptr;

struct utest *current;

void
print_results(void) {
    struct utest *tmp = dummy.ptr;
    printf("Tests found: %d\n", num_tests);
    if (!tmp)
        return;
    while (tmp) {
        if (tmp->failed)
            printf("*");
        else
            printf("'");
        tmp = tmp->ptr;
    }
    printf("\n");
    tmp = dummy.ptr;
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
    struct utest *tmp = (struct utest *)malloc(sizeof(struct utest));
    if (!num_tests)
        dummy.ptr = current = tmp;
    else
        current->ptr = tmp;
    current = tmp;
    current->title = (char *)malloc(strlen(desc) + 1);
    strcpy(current->title, desc);
    current->failed = 0;
    reasons_ptr = current->reasons;
    current->ptr = NULL;
    (*fn)();
    num_tests++;

}

int
assert_equals_number(const char *reason, long double expected, long double actual) {
    if (expected == actual)
        return 1;
    current->failed++;

    char *ex_ac = expected_actual_string(INT, &expected, &actual);
    *reasons_ptr = (char *)malloc(strlen(reason) + strlen(ex_ac) + 1);
    strcpy(*reasons_ptr, reason);
    strcat(*reasons_ptr++, ex_ac);
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


