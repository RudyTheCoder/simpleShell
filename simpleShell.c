#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 1000

// Function to execute a command
void command(char *buffer) {
    // Fork a new process
    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Failed to fork a new process\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        
        // Tokenize the input command
        char *args[MAX_LENGTH];
        char *token = strtok(buffer, " \t\n");
        int i = 0;
        
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        
        args[i] = NULL;
        
        // Execute the command
        if (execvp(args[0], args) == -1) {
            printf("Failed to execute command: %s\n", buffer);
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        
        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char buffer[MAX_LENGTH];
    printf("Type 'exit' to quit\n");
    
    while (1) {
        printf("Simple Shell # ");
        
        // Read user input
        if (fgets(buffer, MAX_LENGTH, stdin) == NULL) {
            break;
        }
        
        // Check for the 'exit' command
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }
        
        // Execute the entered command
        command(buffer);
    }
    
    return 0;
}
