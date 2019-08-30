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

int comparison(char *command, char*str) {
	for(int i=0;i<strlen(str);i++) {
		if(command[i] != str[i]) {
			return 0;
		}
	}
	return 1;
}

void currentDirectory() {
	char s[100];
	printf("%s\n",getcwd(s,100));
}

int changeDirectory(char *path) {

	char *str = malloc(sizeof(char)*(strlen(path)-1));
	for(int i=0;i<strlen(path)-1;i++) {
		str[i] = path[i];
	}

	if(path == NULL || strlen(path) == 0) {
		printf("Path Argument missing\n");
		return -2;
	}
	//printf("%ld",strlen(path));
	//printf("%ld",strlen("chanda"));
	//printf("%s",path);
	currentDirectory(); 
	int status = chdir(str);
	currentDirectory();

	return status;
}

void builtin_commands(char **tokens) {
	char *command = *tokens;
	if(comparison(command,"cd") == 1) {
		int status = changeDirectory(*(++tokens));
		if(status == -1) {
			printf("error : Cannot find the directory.\n");
		}
		return;
	}
	else if(comparison(command,"echo") == 1) {
		++tokens;
		while(*tokens != NULL) {
			printf("%s ",*tokens);
			tokens++;
		}
	}
	else if(comparison(command,"history") == 1) {
		print_history();
	}

	else if(comparison(command,"pwd") == 1) {
		currentDirectory();
	}

	else if(comparison(command,"exit") == 1) {
		exit(0);
	}

	else {
		printf("Please enter a valid command...");
	}
	
}

void init_shell() {
	while(1) {
		printf(">");
		char *command = getCommand();
		add_history(command);
		char **tokens = parser(command);
		builtin_commands(tokens);
		//print_history();
	}
}

void main() {
	init_shell();
}