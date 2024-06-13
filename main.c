/*
 *  Name: Ahmed Kallab
 *  Program Summary:This program demonstrates inter-process communication between a parent and child process
 *  using Unix pipes. The parent sends predefined messages to the child, which then reads the messages, prompts
 *  the user for a response, and sends the response back to the parent.
 *
 * Readme file is available!
 * */

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE] = "Greetings son";
    char write_msg2[BUFFER_SIZE] = "How are you son";
    char parent_read_msg[BUFFER_SIZE];
    char child_write_msg[BUFFER_SIZE];
    char child_read_msg[BUFFER_SIZE];
    int parent_to_child[2];
    int child_to_parent[2];
    pid_t pid;
    bool State = true;
    int counter = 0;

    while (State) {
        /* create the pipes */
        if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
            fprintf(stderr, "Pipe failed");
            return 1;
        }

        /* fork a child process */
        pid = fork();
        if (pid < 0) {
            /* error occurred */
            fprintf(stderr, "Fork Failed");
            return 1;
        }

        if (pid > 0) {
            /* parent process */
            /* close the unused ends of the pipes */
            close(parent_to_child[READ_END]);
            close(child_to_parent[WRITE_END]);

            /* write to the pipe */
            if (counter == 0)
            {
                write(parent_to_child[WRITE_END], write_msg, strlen(write_msg) + 1);
            }
            else if (counter == 1)
            {
                write(parent_to_child[WRITE_END], write_msg2, strlen(write_msg2) + 1);
            }
            else
            {
                break;
                return 0;
            }

            /* close the write end of the pipe to signal the child */
            close(parent_to_child[WRITE_END]);

            /* read the response from the child */
            read(child_to_parent[READ_END], parent_read_msg, BUFFER_SIZE);
            printf("%s", parent_read_msg);

            /* close the read end of the pipe */
            close(child_to_parent[READ_END]);

            /* Wait for the child to process the message */
            sleep(2);
        }
        else
        {
            /* child process */
            /* close the unused ends of the pipes */
            close(parent_to_child[WRITE_END]);
            close(child_to_parent[READ_END]);

            /* read from the pipe */
            read(parent_to_child[READ_END], child_read_msg, BUFFER_SIZE);
            printf("%s\n", child_read_msg);

            /* get user input */
            fgets(child_write_msg, BUFFER_SIZE, stdin);

            /* close the read and write ends of the pipes */
            close(parent_to_child[READ_END]);
            close(child_to_parent[WRITE_END]);

            /* Exit the child process */
            return 0;
        }

        /* Increment the counter */
        counter++;
    }
    return 0;
}
