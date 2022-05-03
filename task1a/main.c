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
            write = system_call(SYS_WRITE,to, strcat(itoa(res),"\n"), 3);
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
    int flag;
    char str[50];
    for (k = 1; k <argc; k++) {
        strcat(str,argv[k] + 2);
        if(argv[k][1] == 'D') {
            flag = 'D';
        }
        else if(argv[k][1] == 'i') {
            file_from = system_call(SYS_OPEN,str, 000, 0644);
        }
        else if(argv[k][1] == 'o'){
            file_to = system_call(SYS_OPEN,str, 101, 0644);
        }
    }

    if (flag == 'D') {
        D_flag(file_from,file_to);
    }
    else {
        char* c = itoa(222);
        int res = 0;
        int len = system_call(SYS_READ,file_from, c, 1);
        while (len != 0) {
            if(*c != ' ' && *c != '\n') {
                res++;
                ClearSpaces1(c, len);
            }
            else if( *c == '\n') {
                system_call(SYS_WRITE,file_to, strcat(itoa(res),"\n"), 2);
                res = 0;
                len = system_call(SYS_READ,file_from, c, 1);
            }
        }
    }

    return 0;
}
