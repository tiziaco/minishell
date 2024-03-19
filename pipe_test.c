#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid_ls, pid_wc;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    printf("Pipe IN: %d\n", pipefd[1]);
    printf("Pipe OUT: %d\n", pipefd[0]);
    printf("Parent process ID: %d\n", getpid());
    // Fork a child process for ls
    pid_ls = fork();

    if (pid_ls == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid_ls == 0)
    { // Child process for ls
        printf("Child process executing command: %s\n", "ls");
    	printf("Child process ID: %d\n", getpid());
        // Close the read end of the pipe

        close(pipefd[0]);
        
        // Redirect stdout to write to the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // Close the write end of the pipe

        // Execute ls command
        execlp("ls", "ls", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }
    waitpid(pid_ls, NULL, 0);
    // Fork a child process for wc
    pid_wc = fork();

    if (pid_wc == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid_wc == 0) { // Child process for wc
        printf("Child process executing command: %s\n", "wc");
    	printf("Child process ID: %d\n", getpid());
        // Close the write end of the pipe
        close(pipefd[1]);
        
        // Redirect stdin to read from the pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // Close the read end of the pipe

        // Execute wc command
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    // Close unused ends of the pipe in the parent process
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes to finish
    
    waitpid(pid_wc, NULL, 0);

    return 0;
}
