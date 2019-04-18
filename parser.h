
#define TRUE 1
#define FALSE 0

char *read_stdin (void);
typedef int bool;
bool isEqual(char *str1, char *str2);
bool isEqualCase(char *str1, char *str2, bool caseInsensitive);
char *strtoupper(char *str1);