#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    // Get the host name
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));
    printf("Hostname: %s\n", hostname);

    // Get the system information
    struct utsname unameData;
    if (uname(&unameData) != -1) {
        printf("System: %s %s %s %s %s\n",
               unameData.sysname,
               unameData.nodename,
               unameData.release,
               unameData.version,
               unameData.machine);
    } else {
        printf("Failed to retrieve system information.\n");
    }

    // You can add more system information retrieval code here

    return 0;
}
