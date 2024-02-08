#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_comments(char* line) {
    char* comment_pos = strchr(line, '#'); // Find the position of the '#' character
    if (comment_pos != NULL) {
        *comment_pos = '\0'; // Replace '#' with a null terminator to remove the comment
    }
}

int main() {
    char input[256];
    printf("Enter a command: ");
    fgets(input, sizeof(input), stdin); // Read the input command from the user
    
    remove_comments(input); // Remove the comment from the input command
    
    printf("Command without comments: %s", input);
    
    return 1;
}

