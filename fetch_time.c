#include <stdio.h>
#include <time.h>

int main() {
    // Declare a variable to hold the current time
    time_t current_time;

    // Get the current time
    current_time = time(NULL);

    // Convert the current time to a string
    char* time_string = ctime(&current_time);

    // Print the current time
    printf("Current time: %s", time_string);

    return 0;
}
