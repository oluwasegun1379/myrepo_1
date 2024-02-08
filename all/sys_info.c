#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname sys_info;
    if (uname(&sys_info) != -1) {
        printf("System Information:\n");
        printf("  System Name: %s\n", sys_info.sysname);
        printf("  Node Name: %s\n", sys_info.nodename);
        printf("  Release: %s\n", sys_info.release);
        printf("  Version: %s\n", sys_info.version);
        printf("  Machine: %s\n", sys_info.machine);
    } else {
        perror("uname");
    }
    return 0;
}
