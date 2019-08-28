#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void clear() {
  printf("\033[H\033[J");
}

char *reading_command() {
  ssize_t buffsize = 0; 
  char *command = NULL;
  getline(&command, &buffsize, stdin);
  return command;
}

char **parser(char *command) {
  char **tokens = malloc(sizeof(command));
  char *token;
  
  token = strtok(command," ");
  int i = 0;
  while(token) {
    tokens[i] = token;
    i++;
    token = strtok(NULL," ");
  }
  tokens[i] = NULL;
  return tokens;
}

void main() {

}