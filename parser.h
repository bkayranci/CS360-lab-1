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
    char *name; //name of the person
    char *sex; //M or F are the only allowed options
    Dllist children; //pointers to the children People structs
    void *mother; //pointer to mother struct
    void *father; //pointer to father struct
    int visited; //0 for not visited, 1 for visited, usefull for BFS and DFS
} Person;
//checks if a person is already a child in the dllist, and inserts it if it isn't
void insert_child(Person *p, Dllist children);
//Function to iterate through the tree and print it out
//TO DO: Once cycle detection is done add code to print tree out in right order
void print_fam(JRB people);
//DFS function to test for cycles in the family tree
//returns 1 if the graph is cyclical and 0 otherwise
int is_desc(Person*P);
//new_person creates and returns a pointer to a Person struct.
Person *new_person(char *name, JRB people);
//returns full name of the person read in
char *getName(IS is);