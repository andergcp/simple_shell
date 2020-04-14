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
/* Aux_fun_1 */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
void _strcpy(char *dest, char *src);
/* Aux_fun_2 */
void clear_paths(char **paths);
int _atoi(char *s);
void c_buf(char *buff);
char *_itoa(int num);
/*Env_fun*/
env_v *set_env_v(char **env);
void clear_env(variables *m_v);
char *get_env(variables *m_v, char *name);
void set_env(variables *m_v, char *name, char *value);
/* Built-in functions */
/* Built_fun_1 */
int comm_cd(variables *m_v);
int comm_he(variables *m_v);
int comm_ex(variables *m_v);
int comm_en(variables *m_v);
int comm_his(variables *m_v);
int comm_unset(variables *m_v);
int comm_set(variables *m_v);
/* Basic functions */
/* Basic_fun_1 */
void _getptr(variables *m_v);
void _getoken(variables *m_v);
void _execute(variables *m_v, char *args);
char *handle_path(variables *m_v);
int manage_command(variables *m_v);
/* Basic_fun_2 */
inside *dic_command();
char **_strtok_line(char *ptr);
char **_strtok_path(char *ptr);
char *get_path(variables *m_v);
void error_msg(variables *m_v, char *msg);



#endif
