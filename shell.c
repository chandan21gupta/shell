#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *reading_command() {
  char *command = NULL;
  ssize_t buffsize = 0; 
  getline(&command, &buffsize, stdin);
  return command;
}

void main() {

}