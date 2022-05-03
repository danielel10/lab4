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



int ClearSpaces1 (char * c, int len, int from) {
    int len1 = len;
    while (len1 != 0) {
        if(*c == ' ') {
            while (*c == ' ')
                system_call(SYS_READ,from, c, 1);
            return len1;
        }
        else if( *c != ' ' && *c != '\n') {
            len1 = system_call(SYS_READ,from, c, 1);
            if (len1 == 0)
                return len1;
        }
        else
            return len1;
    }
    return len1;

}

int print_to_err(int call_id, int response, int flag) {
    if (flag == 'D') {
        system_call(SYS_WRITE, STDERR, strcat(itoa(call_id), "\n"), 3);
        system_call(SYS_WRITE, STDERR, strcat(itoa(response), "\n"), 3);
    }
    return 0;
}

int ClearSpaces1err (char * c, int len, int from) {
    int len1 = len;
    while (len1 != 0) {
        if(*c == ' ') {
            while (*c == ' ') {
                len1 = system_call(SYS_READ,from, c, 1);
                print_to_err(SYS_READ,len1);
            }

            return len1;
        }
        else if( *c != ' ' && *c != '\n') {
            len1 = system_call(SYS_READ,from, c, 1);
            print_to_err(SYS_READ,len1);
            if (len1 == 0)
                return len1;
        }
        else
            return len1;
    }
    return len1;

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
            len = ClearSpaces1err(c, len, from);
        }
        else if( *c == '\n') {
            write = system_call(SYS_WRITE,to, strcat(itoa(res),"\n"), 3);
            print_to_err(SYS_WRITE,write);
            res = 0;
            len = system_call(SYS_READ,from, c, 1);
            print_to_err(SYS_READ,len);
        }
        if(len == 0 && *c != '\n') {
            write = system_call(SYS_WRITE,to, strcat(itoa(res),"\n"), 2);
            print_to_err(SYS_WRITE,write);
        }
        if(from != STDIN) {
            int r = system_call(SYS_CLOSE,from, c, 1);
            print_to_err(SYS_CLOSE,r);
        }

        if(to != STDOUT) {
            int t = system_call(SYS_CLOSE,to, c, 1);
            print_to_err(SYS_CLOSE,t);
        }


    }

    return 0;
}


void reset_string(char* string, int size) {
    int k;
    for (k = 0; k < size; k++)
        string[k] = '\0';

}

int main (int argc , char* argv[], char* envp[]) {
    int k;
    int file_to = STDOUT;
    int file_from = STDIN;
    int flag;
    char str[50];
    for (k = 1; k <argc; k++) {
        reset_string(str,50);
        strcat(str,argv[k] + 2);
        if(argv[k][1] == 'D') {
            flag = 'D';
        }
        else if(argv[k][1] == 'i') {
            file_from = system_call(SYS_OPEN,str, 000, 0644);
            if(file_from < 0)
                system_call(1);
            if(flag == 'D')
                print_to_err(SYS_OPEN,file_from);

        }
        else if(argv[k][1] == 'o'){
            file_to = system_call(SYS_OPEN,str, 101, 0644);
            if(file_to < 0)
                system_call(1);
            if(flag == 'D')
                print_to_err(SYS_OPEN,file_to);
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
                len = ClearSpaces1(c, len, file_from);

            }
            else if( *c == '\n') {
                system_call(SYS_WRITE,file_to, strcat(itoa(res),"\n"), 2);
                res = 0;
                len = system_call(SYS_READ,file_from, c, 1);
            }
            if(len == 0 && *c != '\n') {
                system_call(SYS_WRITE,file_to, strcat(itoa(res),"\n"), 2);
            }

        }
        if(file_from != STDIN)
            system_call(SYS_CLOSE,file_from, c, 1);
        if(file_to != STDOUT)
            system_call(SYS_CLOSE,file_to, c, 1);
    }

    return 0;
}
