#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include <ctype.h>
#include "./libfdr/dllist.h"
#include "./libfdr/jrb.h"
#include "./libfdr/jval.h"
#include "./libfdr/fields.h"

typedef struct Person {
   char  Name[50];
   char  Sex[1];
   struct Person *Father;
   struct Person *Mother;
   struct Dllist *Children;
} Person;

char *read_stdin() {
    int buffer_size = 10;
    char *text = malloc(sizeof(char) * buffer_size);
    char *buffer = malloc(sizeof(char) * buffer_size);
    while(fgets(buffer, buffer_size, stdin)){
        text = realloc(text, strlen(text)+strlen(buffer));
        strcat(text, buffer);
    }
    
    return text;
}

char *test() {

    char *text = read_stdin();
    char *delimiter = " ";
    printf("%s", text);
    
    char *ptr = strtok(text, delimiter);
    while(ptr != NULL){
        printf("%s\n", ptr);
        ptr = strtok(NULL, delimiter);
    }
    return "test";
}

char  *strtoupper(char str[]) {

    for(int i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }

    return str;
}

bool isEqualCase(char *str1, char *str2, bool caseInsensitive) {
    if (caseInsensitive) {
        
        if ( strcmp( strtoupper(str1), strtoupper(str2) ) == 0 ) {
            return TRUE;
        }
        return FALSE;
    }
    if (strcmp(str1, str2) == 0) {
        return TRUE;
    }
    return FALSE;
}

bool isEqual(char *str1, char *str2) {
    return isEqualCase(str1, str2, TRUE);
    
}

int main(int argc, char const *argv[]) {

    IS is;
    is = new_inputstruct(argv[1]); // belirtilen dosyayi IS yapisinda oku
    JRB root = make_jrb();
    while(get_line(is) != -1){
        char *text = is->text2;
        char person_text[] = {"PERSON"};
        
        if (isEqual(text, person_text)) {
            

        } else {
            
        }
        
        
    }
        
    
    
    return 0;
}