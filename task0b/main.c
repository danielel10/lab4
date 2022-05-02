#include "util.h"

extern int system_call();


#define SYS_WRITE 4
#define SYS_READ 3
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define STDOUT 1

int main (int argc , char* argv[], char* envp[]) {


    int file_descriptor = system_call(SYS_OPEN,argv[1], 0x001, 0644);
    if (file_descriptor < 0) {
        system_call(0x56);
    }
    system_call(SYS_LSEEK, file_descriptor,0x506,0);
    system_call(SYS_WRITE, file_descriptor, "Mira", 5 );
    return 0;
}
