#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* new_path = "/usr/local/bin:/usr/bin:/bin";  // New value for PATH
    
    // Set the environment variable PATH to the new value
    int result = setenv("PATH", new_path, 1);
    
    if (result != 0) {
        printf("Error setting PATH environment variable.\n");
        return 1;
    }
    
    printf("PATH environment variable set to: %s\n", new_path);
    
    return 0;
}

