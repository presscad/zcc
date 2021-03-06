/*
 * ================================
 * eli960@qq.com
 * http://www.mailhonor.com/
 * 2018-07-12
 * ================================
 */

#include "zcc.h"
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int runover = 0;
static void *foo(void *arg)
{
    for (int i = 0; i < 10; i++) {
        struct hostent *hp = gethostbyname((char *)arg);
        zcc::msleep(rand()%1000);
        if (hp) {
            printf("%s: %s\n", (char *)arg, hp->h_name);
        } else {
            printf("%s: not found\n", (char *)arg);
        }
    }
    runover++;
    return 0;
}

static void *foo2(void *arg) 
{
    while(runover!=2) {
        sleep(1);
    }
    zcc::var_proc_stop = true;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        printf("%s domain1 domain2\n", argv[0]);
        return 0;
    }
    zcc::coroutine_base_init();
    zcc::coroutine_go(foo, argv[1]);
    zcc::coroutine_go(foo, argv[2]);
    zcc::coroutine_go(foo2, 0);
    zcc::coroutine_base_loop();
    zcc::coroutine_base_fini();
    return 0;
}
