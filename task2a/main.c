#include "util.h"
#include <limits.h>
#include <dirent.h>
extern int system_call();
extern void infection();


#define SYS_WRITE 4
#define SYS_READ 3
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define STDOUT 1
#define STDIN 0
#define STDERR 2
#define SYS_GETDENTS 141

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
    system_call(SYS_OPEN,".",0,0777);
    infection(2);
    char buf[8192];
    int fd;
    struct linux_dirent *d;
    int count;
    int i;
    int flag;
    int write;
    char prefix[8192];
    int prefix_len;
    char d_type;
    for (i = 1; i < argc ; i++) {
        if(argv[i][1] == 'D')
            flag = 'D';
        else if(argv[i][1] == 'p') {
            prefix_len = strlen(argv[i] - 2);
            flag = 'p';
            strcat(prefix,argv[i] + 2);
        }

    }
    fd = system_call(SYS_OPEN,".",0,0777);
    print_to_err(SYS_OPEN,fd,flag);
    if(fd < 0)
        system_call(1);
    int bpos;
    d = (struct linux_dirent *) buf;

    for ( ; ; ) {
        count = system_call(SYS_GETDENTS,fd,d,8192);
        print_to_err(SYS_GETDENTS,count,flag);
        for (bpos = 0; bpos < count;) {
            d = (struct linux_dirent *) (buf + bpos);
            d_type = *(buf + bpos + d->d_reclen - 1);
            if(flag == 'p') {
                if(strncmp(prefix,d->d_name, prefix_len) == 0) {
                    write = system_call(SYS_WRITE,STDOUT, strcat(d->d_name, "\n"), strlen(d->d_name) + 1);
                    print_to_err(SYS_WRITE,write,flag);
                }

            }
            else {
                write = system_call(SYS_WRITE,STDOUT, strcat(d->d_name, "\n"), strlen(d->d_name) + 1);
                print_to_err(SYS_WRITE,write,flag);
                system_call(SYS_WRITE,STDOUT, itoa(d_type),1);
            }
            bpos = bpos + d->d_reclen;


        }
        return 0;
    }


}
