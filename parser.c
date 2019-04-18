#include "./libfdr/dllist.h"
#include "./libfdr/jrb.h"
#include "./libfdr/fields.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char * name; //name of the person
    char * sex; //M or F are the only allowed options
    Dllist children; //pointers to the children People structs
    void * mother; //pointer to mother struct
    void * father; //pointer to father struct
    int visited; //0 for not visited, 1 for visited, usefull for BFS and DFS
} Person;
//checks if a person is already a child in the dllist, and inserts it if it isn't
void insert_child(Person * p, Dllist children);
//Function to iterate through the tree and print it out
//TO DO: Once cycle detection is done add code to print tree out in right order
void print_fam(JRB people);
//DFS function to test for cycles in the family tree
//returns 1 if the graph is cyclical and 0 otherwise
int is_desc(Person* P);
//new_person creates and returns a pointer to a Person struct.
Person * new_person(char * name, JRB people);
//returns full name of the person read in
char * getName(IS is);
main(int argc, char ** argv)
{
    Dllist search;
    JRB people, tmp;
    IS is;
    int i, nsize;
    Person * p; //stands for person
    Person * f; //stands for family
    Person * tmpP;
    char * name;
    char * option; //PERSON, FATHER, MOTHER etc...
    int found; //used for searching Dllists
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./famtree filename\n");
        exit(1);
    }
    people = make_jrb();
    is = new_inputstruct(argv[1]);
    if (is == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    while(get_line(is) >= 0)
    {
        option = strdup(is->fields[0]);
        //fill out Person properties based on first field read of each line
        if (strcmp(option, "PERSON")== 0)
        {
            name = strdup(getName(is));
            tmp = jrb_find_str(people, name);
            if (tmp == NULL) {
                p = new_person(name, people);
            }
            else {
                p = (Person *) tmp->val.v;
            }
        }
        else if (strcmp(option, "FATHER") == 0)
        {
            name = strdup(getName(is));
            tmp = jrb_find_str(people, name);
            if (tmp == NULL) {
                f = new_person(name, people);
            }
            else {
                f = (Person *) tmp->val.v;
            }
            p->father = f;
            f->sex = "Male";
            insert_child(p, f->children);
        }
        else if (strcmp(option, "MOTHER") == 0)
        {
            name = strdup(getName(is));
            tmp = jrb_find_str(people, name);
            if (tmp == NULL) {
                f = new_person(name, people);
            }
            else {
                f = (Person *) tmp->val.v;
            }
            p->mother = f;
            f->sex = "Female";
            insert_child(p, f->children);
        }
        else if (strcmp(option, "FATHER_OF") == 0)
        {
            name = strdup(getName(is));
            tmp = jrb_find_str(people, name);
            if (tmp == NULL) {
                f = new_person(name, people);
            }
            else {
                f = (Person *) tmp->val.v;
            }
            f->father = p;
            insert_child(f, p->children);
            p->sex = "Male";
        }
        else if (strcmp(option, "MOTHER_OF") == 0)
        {
            name = strdup(getName(is));
            tmp = jrb_find_str(people, name);
            if (tmp == NULL) {
                f = new_person(name, people);
            }
            else {
                f = (Person *) tmp->val.v;
            }
            f->mother = p;
            p->sex = "Female";
            insert_child(f, p->children);
        }
        else if (strcmp(option, "SEX") == 0)
        {
            if(strcmp(is->fields[1], "M") == 0) {
                p->sex = "Male";
            }
            else if (strcmp(is->fields[1], "F") == 0) {
                p->sex = "Female";
            }
            else
            {
                printf("Error, only M or F can be read for sex\n");
            }
        }
    }
    jrb_traverse(tmp, people)
    {
        p = (Person *) tmp->val.v;
        if(is_desc(p) == 1)
        {
            printf("Error, graph has cycles\n");
            exit(1);
        }
    }
    print_fam(people);
}
Person * new_person(char * name, JRB people)
{
    Person * p;
    p = malloc(sizeof(Person));
    p->name = strdup(name);
    p->children = new_dllist();
    p->visited = 0;
    jrb_insert_str(people, name, new_jval_v((void *) p));
    return p;
}
int is_desc(Person * p)
{
    Dllist tmp;
    Person * child;
    if (p->visited == 1) {
        return 0;
    }
    if (p->visited == 2) {
        return 1;
    }
    p->visited = 2;
    dll_traverse(tmp, p->children)
    {
        child = (Person *) tmp->val.v;
        if (is_desc(child)) {
            return 1;
        }
    }
    p->visited = 1;
    return 0;
}
void print_fam(JRB people)
{
    char * motherName;
    char * fatherName;
    Person * mother;
    Person * father;
    Person * p;
    Person * child;
    JRB tmp;
    Dllist children;
    jrb_traverse(tmp, people)
    {
        p = (Person *) tmp->val.v;
        father = (Person *) p->father;
        if (father == NULL) {
            fatherName = "Unknown";
        }
        else
        {
            fatherName = father->name;
        }
        mother = (Person *) p->mother;
        if (mother == NULL) {
            motherName = "Unknown";
        }
        else
        {
            motherName = mother->name;
        }
        printf("%s \n", p->name);
        if(p->sex != NULL) {
            printf(" Sex: %s\n", p->sex);
        }
        printf(" Father: %s\n", fatherName);
        printf(" Mother: %s\n", motherName);
        printf(" Children:");
        if(dll_empty(p->children) != 1)
        {
            dll_traverse(children, p->children)
            {
                child = (Person *) children->val.v;
                printf("\n %s", child->name);
            }
            printf("\n\n");
        }
        else {
            printf("none\n\n");
        }
    }
}
char * getName(IS is)
{
    char * name;
    int nsize, i;
    nsize = strlen(is->fields[1]);
    for (i = 2; i < is->NF; i++) {
        nsize += (strlen(is->fields[i] + 1));
    }
    name = (char *) malloc(sizeof(char) * (nsize+1));
    strcpy(name, is->fields[1]);
    nsize = strlen(is->fields[1]);
    for (i = 2; i < is->NF; i++)
    {
        name[nsize] = ' ';
        strcpy(name+nsize+1, is->fields[i]);
        nsize += strlen(name+nsize);
    }
    return name;
}
void insert_child(Person * p, Dllist children)
{
    Dllist search;
    Person * tmp;
    int found;
    //check if the list is empty, and if so automatically insert child
    if (dll_empty(children) == 1) {
        dll_append(children, new_jval_v(p));
    }
    else
    {
        //The list is not empty, so check to see if the child is already in the list
        dll_traverse(search, children)
        {
            tmp = (Person *) search->val.v;
            if (strcmp(p->name, tmp->name) == 0) {
                found = 1;
            }
        }
        if (found == 0) {
            dll_append(children, new_jval_v(p));
        }
    }
}
