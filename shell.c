#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *history[100];
int command_number = 0;

void add_history(char *command) {
    history[command_number] = malloc(strlen(command)*sizeof(char));
    command_number++;
}

void print_history() {
    for(int i = 0;i<command_number;i++) {
        printf("%s",history[i]);
    }
}

char *getCommand() {
    char *command = NULL;
    ssize_t buffsize = 0;
    getline(&command,&buffsize,stdin);
    return command;
}

void main() {
    
}