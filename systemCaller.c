#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

int executeCommand(char* command[]);
int parseInput(char* input, char* splitWord[]);
void changeDirectories(char * directory);

int main() {
    char input[512];
    char *command[64];
    int wordNum;
    while (1) { // lol
        printf("_exampleShell<rborenstein>&_");
        fgets(input, 256, stdin);
        printf("\n");
        wordNum = parseInput(input, command);
        if (strcmp(command[0], "exit") == 0) {
            return 0;
        } else if (strcmp(command[0], "cd") == 0) {
            if(wordNum != 2){
                printf("Path Not Found!\n");
            }else{
                changeDirectories(command[1]);
            }
        } else {
            if (executeCommand(command) == 1) {
                printf("Execution error.\n");
            }
        }
    }
}


int executeCommand(char* command[]) {
    int processId, execvpError = 0;
    if((processId = fork()) < 0 ){ // fail
        printf("fork failed!\n");
    }else if(processId == 0){ // child
        if(execvp(*command, command) == -1){
            execvpError = 1;
        }
    }else{
        wait(NULL);
    }
    return execvpError;
}


int parseInput(char* input, char* splitWords[]) {
    int wordInd = 0;
    splitWords[0] = strtok(input, " \n");
    while (splitWords[wordInd] != NULL) {
        splitWords[++wordInd] = strtok(NULL, " \n");
    }
    return wordInd;
}

void changeDirectories(char * directory){
    if(chdir(directory) < 0){
        printf("Path Not Found!\n");
    }
}
