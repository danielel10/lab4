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

typedef struct linux_dirent {
    unsigned long  d_ino;     /* Inode number */
    unsigned long  d_off;     /* Offset to next linux_dirent */
    unsigned short d_reclen;  /* Length of this linux_dirent */
    char           d_name[];  /* Filename (null-terminated) */
    /* length is actually (d_reclen - 2 -
       offsetof(struct linux_dirent, d_name) */
    /*
    char           pad;       // Zero padding byte
    char           d_type;    // File type (only since Linux 2.6.4;
                              // offset is (d_reclen - 1))
    */

}linux_dirent;

int print_to_err(int call_id, int response, int flag) {
    if (flag == 'D') {
        system_call(SYS_WRITE, STDERR, strcat(itoa(call_id), "\n"), 3);
        system_call(SYS_WRITE, STDERR, strcat(itoa(response), "\n"), 3);
    }
    return 0;
}


int main (int argc , char* argv[], char* envp[]) {
    char buf[8192];
    int fd;
    linux_dirent *d;
    int count;

    fd = system_call(SYS_OPEN,".",0,0644);
    if(fd < 0)
        system_call(1);
    int bpos;

    for ( ; ; ) {
        count = system_call(141,fd,buf,8192);
        for (bpos = 0; bpos < count;) {
            d = (struct linux_dirent *) (buf + bpos);
            system_call(SYS_WRITE,STDOUT, strcat(d->d_name, "\n"), strlen(d->d_name) + 1);
            bpos += d->d_reclen;
        }
        return 0;
    }


}
