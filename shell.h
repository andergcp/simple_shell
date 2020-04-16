#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

extern char **environ;
/**
 * struct env_variable - Node's struct for enviroment variables
 * @name: name of the variable
 * @value: Value asigned to name
 * @next: Pointer to next node
 */
typedef struct env_variable
{
	char *name;
	char *value;
	struct env_variable *next;
} env_v;

/**
 * struct main_variables - Set of variables used in the program
 * @argv: Arguments received from main
 * @ptr: stores string received from stdin
 * @args: array of pointers to arguments
 * @env: array of pointers to environment variables
 * @status: status of the las process
 * @prompt_n: number of lines received from stdin
 * @p_env: head of linked list of enviroment variables
 * @diccio: pointer to list of built-ins values
 */
typedef struct main_variables
{
	char **argv;
	char **env;
	char *ptr;
	char **args;
	int status;
	int prompt_n;
	struct env_variable *p_env;
	struct inside_functions *diccio;
} vari;
/**
 * struct inside_functions - values of built-ins
 * @command: name of the built-ins
 * @command_function: pointer to function
 * @help: pointer to help files
 */
typedef struct inside_functions
{
	char *command;
	void (*command_function)();
	char *help;
} inside;
/* basic functions 1*/
/*inside *dic_command();*/
int manage_command(vari *m_v);
void _execute(vari *m_v, char *path);
/* basic functions 2*/
void _strtok_line(vari *m_v);
char **_strtok_path(char *path);
/* aux functions 1*/
void error_msg(vari *m_v, char *msg);
int _strlen(char *s);
void _strcpy(char *dest, char *src);
int _atoi(char *s);
char *_itoa(int num);
int _strcmp(char *s1, char *s2);
char *_strdup(char *s);
char *_strcat(char *dest, char *src);
void clear_paths(char **paths);
void comm_en(vari *m_v);
void comm_ex(vari *m_v);
void clear_env(vari *m_v);
/* environment functions */
void _addnode(vari *m_v, char *name, char *value);
char *_getnode(vari *m_v, char *name);
void _getenv(vari *m_v);
void c_buf(char *buff);
char **_envtoarray(vari *vars);
inside *dic_command();

#endif
