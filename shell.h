#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/*
typedef struct inside_functions{
	char * command;
	int (*command_function)();
} inside;
int comm_cd (char **a);
int comm_he (char **a);
int comm_ex (char **a);
int comm_en (char **a);
int comm_his (char **a);

inside array_comm[] = {
	{"cd", &comm_cd}, 
	{"help", &comm_he}, 
	{"exit", &comm_ex},
	{"env", &comm_en},
	{"history", &comm_his},
	{NULL, NULL}
};*/
char *_getptr();
char **_getoken(char *ptr);
void _execute(char **args, char **argv);
void exe_command(char *arg);
#endif
