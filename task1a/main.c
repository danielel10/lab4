#include "util.h"
#include <limits.h>

extern int system_call();


#define SYS_WRITE 4
#define SYS_READ 3
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define STDOUT 1
#define STDIN 0


int main (int argc , char* argv[], char* envp[]) {

    char *input;
    system_call(SYS_READ,STDIN, input, INT_MAX);
    int input_size = strlen(input);
    system_call(SYS_WRITE,STDOUT, itoa(input_size), 1);

    return 0;
}
