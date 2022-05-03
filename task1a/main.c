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
#define STDERR 2



int ClearSpaces1 (char * c, int len) {
    while (len != 0) {
        if(*c == ' ') {
            while (*c == ' ')
                len = system_call(SYS_READ,STDIN, c, 1);
            return 0;
        }
        else if( *c != ' ' && *c != '\n') {
            len = system_call(SYS_READ,STDIN, c, 1);
        }
        else
            return 0;
    }
    return 0;

}




int main (int argc , char* argv[], char* envp[]) {
    char flag = argv[1][1];

    switch (flag) {
        case 'D': {
            char* c = itoa(222);
            int res = 0;
            int len = system_call(SYS_READ,STDIN, c, 1);
            system_call(SYS_WRITE, 0, SYS_READ, 1);
            while (len != 0) {
                if(*c != ' ' && *c != '\n') {
                    res++;
                    ClearSpaces1(c, len);
                }
                else if( *c == '\n') {
                    system_call(SYS_WRITE,STDOUT, itoa(res), 1);
                    system_call(SYS_WRITE,STDOUT, "\n", 2);
                    res = 0;
                    len = system_call(SYS_READ,STDIN, c, 1);
                }
            }

            return 0;
        }

    }

    char* c = itoa(222);
    int res = 0;
    int len = system_call(SYS_READ,STDIN, c, 1);
    while (len != 0) {
            if(*c != ' ' && *c != '\n') {
                res++;
                ClearSpaces1(c, len);
            }
            else if( *c == '\n') {
                system_call(SYS_WRITE,STDOUT, itoa(res), 1);
                system_call(SYS_WRITE,STDOUT, "\n", 2);
                res = 0;
                len = system_call(SYS_READ,STDIN, c, 1);
            }
    }

    return 0;
}
