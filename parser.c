#include "parser.h"

int main(int argc, char **argv)
{
    Out *out;
    out = malloc(sizeof(Out) * 1);
    
    // flag var mi
    if (has_flag("-w", argc, argv) != TRUE) {
        char *success, *error;
        printf("Enter filename if success: ");
        scanf("%ms", &success);
        printf("\nEnter filename if error: ");
        scanf("%ms", &error);
        
        out->success = fopen(success, "w");
        out->error = fopen(error, "w");
    } else {
        out->success = stdout;
        out->error = stderr;
    }
    
    
    JRB people, tmp;
    IS is;
    Person *p;
    Person *f;
    char *name;
    char *option;

    if (argc < 2)
    {
        fprintf(out->error, "usage: ./parser FILENAME\n");
        exit(1);
    }
    people = make_jrb();
    is = new_inputstruct(argv[1]);
    if (is == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    // Her satiri gez
    while(get_line(is) >= 0)
    {
        if ( is->NF == 0 ) {
            continue;
        }

        option = strdup(is->fields[0]);
        
        // Her option icin kosul uygula
        if (strcmp(option, "PERSON")== 0)
        {
            name = strdup(get_name(is));
            tmp = jrb_find_str(people, name);
            if (tmp == NULL) {
                p = new_person(name, people);
            }
            else {
                p = (Person *) tmp->val.v;
            }
        }
        else if (strcmp(option, "FATHER_OF") == 0)
        {
            name = strdup(get_name(is));
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
            name = strdup(get_name(is));
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
        else if (strcmp(option, "FATHER") == 0)
        {
            name = strdup(get_name(is));
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
            name = strdup(get_name(is));
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
                fprintf(out->error, "SEX must be only: M or F\n");
                exit(1);
            }
        }
    }

    // Tum agaci dolas
    jrb_traverse(tmp, people)
    {
        p = (Person *) tmp->val.v;
        
        // Cycle var durumunu kontrol et
        if(is_cycle(p) == 1)
        {
            fprintf(out->error, "ERROR: cycle detected\n");
            exit(1);
        }
    }
    print_tree(people, out);
    return 0;
}

// Yeni Person olustur ve geri dondur
Person *new_person(char *name, JRB people)
{
    Person *p;
    p = malloc(sizeof(Person));
    p->name = strdup(name);
    p->children = new_dllist();
    p->visited = 0;
    jrb_insert_str(people, name, new_jval_v((void *) p));
    return p;
}

// cycle olup olmadigini kontrol et
int is_cycle(Person *p)
{
    Dllist tmp;
    Person *child;
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
        if (is_cycle(child)) {
            return 1;
        }
    }
    p->visited = 1;
    return 0;
}
void print_tree(JRB people, Out *out)
{      
    char *motherName;
    char *fatherName;
    Person *mother;
    Person *father;
    Person *p;
    Person *child;
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
        fprintf(out->success, "%s \n", p->name);
        if(p->sex != NULL) {
            fprintf(out->success, " Sex: %s\n", p->sex);
        }
        fprintf(out->success, " Father: %s\n", fatherName);
        fprintf(out->success, " Mother: %s\n", motherName);
        fprintf(out->success, " Children:");
        if(dll_empty(p->children) != 1)
        {
            dll_traverse(children, p->children)
            {
                child = (Person *) children->val.v;
                fprintf(out->success, "\n %s", child->name);
            }
            fprintf(out->success, "\n\n");
        }
        else {
            fprintf(out->success, "None\n\n");
        }
    }
}

// tam ismini oku
char *get_name(IS is) {
    char *name;
    int nsize, i;
    nsize = strlen(is->fields[1]);
    for (i = 2; i < is->NF; i++)
        nsize += (strlen(is->fields[i] + 1));
    name = (char *) malloc(sizeof(char) *(nsize + 1));
    strcpy(name, is->fields[1]);
    nsize = strlen(is->fields[1]);
    for (i = 2; i < is->NF; i++) {
        name[nsize] = ' ';
        strcpy(name + nsize + 1, is->fields[i]);
        nsize += strlen(name + nsize);
    }

    return name;
}

// child ekle
void insert_child(Person *p, Dllist children)
{
    Dllist search;
    Person *tmp;
    int found;
    // children bossa ekle
    if (dll_empty(children) == 1) {
        dll_append(children, new_jval_v(p));
    }
    else
    {
        // children listesinde zaten ekli degilse ekle
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

// Program verilen flag ile calistirilmis mi
int has_flag (char *flag, int argc, char **argv){
   int idx = 0;

   for (idx = 1; idx < argc;  idx++) {
       if (strcmp(argv[idx], flag) == 0) {
          return TRUE;
       }
    }
    return FALSE;
}
