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


int print_to_err(int call_id, int response, int flag) {
    if (flag == 'D') {
        system_call(SYS_WRITE, STDERR, strcat(itoa(call_id), "\n"), 3);
        system_call(SYS_WRITE, STDERR, strcat(itoa(response), "\n"), 3);
    }
    return 0;
}


int ClearSpaces1 (char * c, int len, int from, int flag) {
    int len1 = len;
    while (len1 != 0) {
        if(*c == ' ') {
            while (*c == ' ') {
                len1 = system_call(SYS_READ,from, c, 1);
                print_to_err(SYS_READ,len1, flag);

            }

            return len1;
        }
        else if( *c != ' ' && *c != '\n') {
            len1 = system_call(SYS_READ,from, c, 1);
            print_to_err(SYS_READ,len1, flag);
            if (len1 == 0)
                return len1;
        }
        else
            return len1;
    }
    return len1;

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
    char inputfile[50];
    char outputfile[50];
    int iflag = 0;
    int oflag = 0;
    for (k = 1; k <argc; k++) {
        if(argv[k][1] == 'D') {
            flag = 'D';
        }
        else if(argv[k][1] == 'i') {
            strcat(inputfile,argv[k] + 2);
            iflag = 1;
            file_from = system_call(SYS_OPEN,inputfile, 000, 0644);
            if(file_from < 0)
                system_call(1);

        }
        else if(argv[k][1] == 'o'){
            strcat(outputfile,argv[k] + 2);
            oflag = 1;
            file_to = system_call(SYS_OPEN,outputfile, 101, 0644);
            if(file_to < 0)
                system_call(1);
        }
    }
    if (flag == 'D') {
        if (iflag == 1) {
            system_call(SYS_WRITE, STDERR, strcat(inputfile,"\n"), strlen(inputfile) + 1);
            print_to_err(SYS_OPEN,file_from, flag);
        }
        if (oflag == 1){
            system_call(SYS_WRITE, STDERR, strcat(outputfile,"\n"), strlen(outputfile) + 1);
            print_to_err(SYS_OPEN,file_to,flag);
        }
    }
        char* c = itoa(222);
        int res = 0;
        int response;
        int len = system_call(SYS_READ,file_from, c, 1);
        print_to_err(SYS_READ,len,flag);
        while (len != 0) {
            if(*c != ' ' && *c != '\n') {
                res++;
                len = ClearSpaces1(c, len, file_from, flag);

            }
            else if( *c == '\n') {
                response = system_call(SYS_WRITE,file_to, strcat(itoa(res),"\n"), 2);
                print_to_err(SYS_WRITE,response,flag);
                res = 0;
                len = system_call(SYS_READ,file_from, c, 1);
                print_to_err(SYS_READ,len,flag);

            }
            if(len == 0 && *c != '\n') {
                response = system_call(SYS_WRITE,file_to, strcat(itoa(res),"\n"), 2);
                print_to_err(SYS_WRITE,response,flag);

            }

        }
        if(file_from != STDIN) {
            response = system_call(SYS_CLOSE,file_from, c, 1);
            print_to_err(SYS_CLOSE,response,flag);

        }
        if(file_to != STDOUT) {
            response = system_call(SYS_CLOSE,file_to, c, 1);
            print_to_err(SYS_CLOSE,response,flag);
        }


    return 0;
}
