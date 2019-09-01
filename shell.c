#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  
#include <sys/wait.h>

//Only 100 commands in total are possible
char *history[100];
int command_number = 0;

void add_history(char *command) {
	if(strlen(command) != 0){
	    history[command_number] = malloc(strlen(command)*sizeof(char));
	    for(int i = 0;i<strlen(command);i++) {
	    	history[command_number][i] = command[i];
	    }
	    command_number++;
	}
}

void print_history() {
    for(int i = 0;i<command_number;i++) {
        printf("%d %s\n",i+1,history[i]);
    }
}

void clear_history() {
	for(int i = 0;i<command_number;i++) {
		free(history[i]);
	}
	command_number = 0;
}

void addHistoryFile() {
	FILE *fptr;
	fptr = fopen("history.txt","w");
	for(int i=0;i<command_number;i++) {
		fputs(history[i],fptr);
		fputs("\n",fptr);
	}
	fclose(fptr);
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

void currentDirectory() {
	char s[100];
	printf("%s\n",getcwd(s,100));
}

int changeDirectory(char *path) {

	if(path == NULL || strlen(path) == 0) {
		printf("Path Argument missing\n");
		return -2;
	}
	int status = chdir(path);

	return status;
}

int execute_process(char **tokens) {
	pid_t pid, wpid;
	int status;
	pid = fork();
	if(pid == 0) {
		if(execvp(*tokens,tokens) == -1) {
			perror("shell");
		}
		exit(0);
	}	else if(pid < 0) {
		perror("shell");
	}
	do {
		wpid = waitpid(pid, &status, WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	return 1;
}

void builtin_commands(char **tokens) {
	char *command = *tokens;
	if(strcmp(command,"cd") == 0) {
		int status = changeDirectory(*(++tokens));
		if(status == -1) {
			printf("error : Cannot find the directory.\n");
			return;
		}
		if(*(++tokens) != NULL) {
			printf("warning : no need for more than one argument\n");
		}
		return;
	}
	else if(strcmp(command,"echo") == 0) {
		tokens++;
		if(*tokens != NULL) {
			if(strcmp(*tokens,"-e") == 0) {
				++tokens;
				while(*tokens != NULL) {
					printf("%s",*tokens);
					tokens++;
				}
				printf("\n");
			}
			else if(strcmp(*tokens,"-n") == 0) {
				++tokens;
				while(*tokens != NULL) {
					printf("%s ",*tokens);
					tokens++;
				}
			}
			else if(strcmp(*tokens,"-en") == 0 || strcmp(*tokens,"-ne") == 0) {
				++tokens;
				while(*tokens != NULL) {
					printf("%s",*tokens);
					tokens++;
				}
			}
			else {
				while(*tokens != NULL) {
					printf("%s ",*tokens);
					tokens++;
				}
				printf("\n");
			}
		}
	}
	else if(strcmp(command,"history") == 0) {
		tokens++;
		if(*tokens == NULL) {
			print_history();
		}
		else if(*tokens != NULL){
			if(strcmp(*tokens,"-c") == 0) {
				clear_history();
			}
			else if(strcmp(*tokens,"-w") == 0) {
				addHistoryFile();
			}
			else if(strcmp(*tokens,"-wc") || strcmp(*tokens,"-cw")) {
				addHistoryFile();
				clear_history();
			}
			else {
				printf("invalid command\n");
				return;
			}
			if(*(++tokens)!=NULL) {
				printf("warning:no need for more than one arguments\n");
			}
		}

	}

	else if(strcmp(command,"pwd") == 0) {
		currentDirectory();
		if(*(++tokens) != NULL) {
			printf("warning : no need for arguments\n");
		}
	}

	else if(strcmp(command,"exit") == 0) {
		if(*(++tokens) != NULL) {
			printf("warning : no need for arguments\n");
		}
		exit(0);
	}

	else if(strcmp(command,"ls") == 0 || strcmp(command,"cat") == 1 || strcmp(command,"date") == 1 || strcmp(command,"rm") || strcmp(command,"mkdir")){
		execute_process(tokens);
	}

	else {
		printf("Command not found\n");
	}	
}

void init_shell() {
	while(1) {
		printf(">");
		char *command = getCommand();
		int len = strlen(command);
		if(len > 0 && command[len-1] == '\n') {
			command[len-1] = '\0';
		}
		add_history(command);
		char **tokens = parser(command);
		builtin_commands(tokens);
		//print_history();
	}
}

void main() {
	init_shell();
}
