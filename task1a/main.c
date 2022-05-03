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
                system_call(SYS_READ,STDIN, c, 1);
            return 0;
        }
        else if( *c != ' ' && *c != '\n') {
            system_call(SYS_READ,STDIN, c, 1);
        }
        else
            return 0;
    }
    return 0;

}

int print_to_err(int call_id, int response) {
    system_call(SYS_WRITE, STDERR, strcat(itoa(call_id), "\n"), 3);
    system_call(SYS_WRITE, STDERR, strcat(itoa(response), "\n"), 3);
    return 0;
}

int ClearSpaces1err (char * c, int len) {
    while (len != 0) {
        if(*c == ' ') {
            while (*c == ' ') {
                len = system_call(SYS_READ,STDIN, c, 1);
                print_to_err(SYS_READ,len);
            }

            return 0;
        }
        else if( *c != ' ' && *c != '\n') {
            len = system_call(SYS_READ,STDIN, c, 1);
            print_to_err(SYS_READ,len);
        }
        else
            return 0;
    }
    return 0;

}




int D_flag(int from,int to) {
    char* c = itoa(222);
    int res = 0;
    int len = system_call(SYS_READ,from, c, 1);
    int write = 0;
    print_to_err(SYS_READ,len);
    while (len != 0) {
        if(*c != ' ' && *c != '\n') {
            res++;
            ClearSpaces1err(c, len);
        }
        else if( *c == '\n') {
            write = system_call(SYS_WRITE,to, itoa(res), 1);
            print_to_err(SYS_WRITE,write);
            write = system_call(SYS_WRITE,to, "\n", 2);
            print_to_err(SYS_WRITE,write);
            res = 0;
            len = system_call(SYS_READ,from, c, 1);
            print_to_err(SYS_READ,len);
        }
    }

    return 0;
}




int main (int argc , char* argv[], char* envp[]) {
    int k;
    int file_to = STDOUT;
    int file_from = STDIN;
    for (k = 1; k <argc; k++) {
        if(argv[k][1] == 'D') {

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
