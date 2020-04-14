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


typedef struct env_variable{
	char *name;
	char *value;
	struct env_variable *next;
} env_v;
typedef struct main_variables{
	char **argv;
	char **env;
	char *ptr;
	char **args;
	int status;
	int prompt_n;
	struct env_variable *p_env;
	struct inside_functions *diccio;
} variables;
typedef struct inside_functions{
	char *command;
	int (*command_function)();
	char *help;
} inside;

/* Auxiliar functions */
int _strcmp(char *s1, char *s2);
char *get_path(variables *m_v);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _atoi(char *s);
void _strcpy(char *dest, char *src);
void c_buf(char *buff);
char *itoa(int num);
void error_msg(variables *m_v, char*msg);
char **_strtok_line(char *ptr);
char **_strtok_path(char *ptr);
env_v *set_env_v(char **env);
void clear_env(variables *m_v);
char *get_env(variables *m_v, char *name);
void set_env(variables *m_v, char *name, char *value);
void clear_paths(char **paths);
/* Built-in functions */
int comm_cd(variables *m_v);
int comm_he(variables *m_v);
int comm_ex(variables *m_v);
int comm_en(variables *m_v);
int comm_his(variables *m_v);
int comm_unset(variables *m_v);
int comm_set(variables *m_v);
void print_env(variables *m_v);
/* Basic functions*/
void _getptr(variables *m_v);
void _getoken(variables *m_v);
void _execute(variables *m_v, char *args);
char *handle_path(variables *m_v);

/*void exe_command(char *arg);*/
int manage_command(variables *m_v);
inside *dic_command();
#endif
