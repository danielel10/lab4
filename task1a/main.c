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


int ClearSpaces (const char * input, int pos, int len) {
    int i;
    for (i = pos; i < len ;) {
        if(input[i] == ' ') {
            while (input[i] == ' ')
                i++;
            return i;
        }
        else
            i++;

    }
    return i;

}

//---------------------------------
int ClearSpaces1 (char * c) {
    while (c != 0) {
        if(c == ' ') {
            while (c != 0 && c == ' ')
                system_call(SYS_READ,STDIN, c, 1);
            return 0;
        }
        else
            system_call(SYS_READ,STDIN, c, 1);
    }
    return 0;

}


//------------------------------------


int main (int argc , char* argv[], char* envp[]) {

    char *input = itoa(222);
    int len = system_call(SYS_READ,STDIN, input, INT_MAX);
    int res = 0;
    int i;
    //---------------------------------
    char* c = itoa(222);
    system_call(SYS_READ,STDIN, c, 1);
    while (c != 0) {
            if((int) c != ' ') {
                res++;
                ClearSpaces1(c);
            }
        system_call(SYS_WRITE,STDOUT, itoa(res), 1);
        system_call(SYS_WRITE,STDOUT, "\n", 2);
        res = 0;
        system_call(SYS_READ,STDIN, c, 1);
    }


    //------------------------------------
    while (len != 0) {
        for (i = 0 ; i < len;) {
            if(input[i] != ' ') {
                res++;
                i = ClearSpaces(input,i, len);

            }
            else {
                i = i + 1;
            }
        }
        system_call(SYS_WRITE,STDOUT, itoa(res), 1);
        system_call(SYS_WRITE,STDOUT, "\n", 2);
        i = 0;
        res = 0;
        len = system_call(SYS_READ,STDIN, input, INT_MAX);
    }

    return 0;
}
