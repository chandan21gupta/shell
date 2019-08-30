#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  

//Only 100 commands in total are possible
char *history[100];
int command_number = 0;

void add_history(char *command) {
	if(strlen(command) != 0){
	    history[command_number] = malloc(strlen(command)*sizeof(char));
	    history[command_number] = command;
	    command_number++;
	}
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

char **parser(char *command) {
	int buffsize = 1024;
	char **tokens = malloc(buffsize*sizeof(char));
	char *token;
	int i = 0;
	token = strtok(command," ");
	while(token != NULL) {
		tokens[i] = token;
		i++;
		if(buffsize<=i) {
			buffsize += 1024;
			tokens = realloc(tokens,buffsize*sizeof(char));
		}
		token = strtok(NULL," ");
	}
	tokens[i] = NULL;
	return tokens;
}

void main() {
	
}