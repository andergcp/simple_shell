#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


typedef struct inside_functions{
	char *command;
	int (*command_function)();
} inside;

/* Auxiliar functions */
int _strcmp(char *s1, char *s2);

/* Built-in functions */
int comm_cd (char **args);
int comm_he (char **args);
int comm_ex (char **args);
int comm_en (char **args);
int comm_his (char **args);

/* Basic functions*/
char *_getptr();
char **_getoken(char *ptr);
void _execute(char **args, char **argv);
/*void exe_command(char *arg);*/
int manage_command(char **args, char **argv);
inside *dic_command();
#endif
