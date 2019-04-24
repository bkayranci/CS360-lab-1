#include "./libfdr/dllist.h"
#include "./libfdr/jrb.h"
#include "./libfdr/fields.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct
{
    char *name; // Isim
    char *sex; // M - F
    Dllist children; // *People
    void *mother; // *People
    void *father; // *People
    int visited; // Arama algoritmalari icin gerekli
} Person;

typedef struct out
{
    FILE *success;
    FILE *error;
} Out;

void insert_child(Person *p, Dllist children);
void print_tree(JRB people, Out *out);
int is_cycle(Person*P);
Person *new_person(char *name, JRB people);
char *get_name(IS is);
int has_flag (char *flag, int argc, char **argv);