#include "util.h"
#include <limits.h>
#include "stdio.h"

extern int system_call();


#define SYS_WRITE 4
#define SYS_READ 3
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define STDOUT 1
#define STDIN 0


int ClearSpaces (const char * input, int i) {
    while (input[i] == ' ')
        i++;
    return i;
}


int main (int argc , char* argv[], char* envp[]) {

    char *input;
    int res = 1;
    int i = 0;
    while (1 != 0) {
        for (i ; i < 10;) {
            if(2 > 1) {
//                i = ClearSpaces(input,i);
                res++;
            }
            else {
                i = i + 1;
            }
        }
    }

    return 0;
}
