#include<stdio.h>
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

void clear() {
    printf("\033[H\033[J");
}

void current_path() {
    char cwd[1024];
    char* username = getenv("USER");
    printf("%s:",username);
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("%s$\n", cwd);
    }
}

void shell_init() {
    clear();
    printf("\n\n\n\n");
    printf("Shell made by Chandan Gupta\n\n");
    printf("Roll Number - 2018386\n");
    printf("\n\n\n\n");
    sleep(2);
    clear();
    current_path();
}

int main() {
    shell_init();
    
}