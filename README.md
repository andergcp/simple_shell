<p align="center"><img src="https://www.holbertonschool.com/holberton-logo.png"></p>

-----
# SIMPLE SHELL

Simple shell is a fundamental command line user interface where you wich provides all basic built-in commands.
This project is our own simple shell with basic commands that was created based on SH. Simple shell handle environment
variables in order to improve functionality of commands such as cd. There are two built-in functions to handle those 
environment variables (setenv, unsetenv).

-----
## INSTALLATION

1. Git clone this repository
  
```bash
 shell:~/root/simple_shell$ git clone https://github.com/andergcp/simple_shell.git
```

2. Compile all files to get executable file

```bash
 shell:~/root/simple_shell$ gcc *.c -o custom_name_shell
```

3. Execute 

```bash
 shell:~/root/simple_shell$ ./custom_name_shell
```

-----
## USAGE

### INTERACTIVE MODE

Interactive mode allows you to enter as many commands as you want.
Also allows you to exit in two ways, press ```CTRL + D``` or 
exit built-in command. ```$ exit ```

To run simple shell just execute the command below

```bash
 shell:~/root/simple_shell$ ./custom_name_shell
```

It will display this screen that means you are inside
```bash
 $ 
```
```bash
shell:~/root/simple_shell$ ./custom_name_shell
 $ echo test
 test
 $ 
```

### NON INTERACTIVE MODE

Non interactive mode allows you to run a simple command.

```bash
 shell:~/root/simple_shell$ echo "command to run" | ./custom_name_shell
```

```bash
 shell:~/root/simple_shell$ echo "ls -l" | ./custom_name_shell
 -rwxrw-r-- 1 vagrant vagrant    30 Feb 20 00:00 custom_name_shell
```

-----
## BUILT-IN COMMANDS

More information about each command use help. ```$ help built-in_command```


```bash
shell:~/root/simple_shell$ ./custom_name_shell
 $ help exit
 Exit the shell.

    Exits the shell with a status of N.  If N is omitted, the exit status
    is that of the last command executed.
 $  
```

| Command | Description  |
| ------- | --- |
| exit | Exit simple shell|
| help | Display help of built-in command |
| env | Display environment variables |
| cd | Change directory |
| setenv | Set environment variable value or create a new one |
| unsetenv | Delete environment variable |

-----
## EXIT STATUS

There are different posible exit status, this deppende on the success of the last command.

0: Success exit.<br> 
2: Error execute command. <br>
126: Permission denied.<br>
127: not found.

-----
## EXAMPLES

### INTERACTIVE MODE

```bash
 shell:~/root/simple_shell$ ./custom_name_shell
 $ ls -l
 -rwxrw-r-- 1 vagrant vagrant    30 Feb 20 00:00 custom_name_shell
 $
```
```bash
 shell:~/root/simple_shell$ ./custom_name_shell
 $ echo 123
 123
 $
```

```bash
 shell:~/root/simple_shell$ ./custom_name_shell
 $ cd /tmp
 $ pwd
 /tmp
 $
```

### NON INTERACTIVE MODE

```bash
 shell:~/root/simple_shell$ echo "/bin/ls -l" | ./custom_name_shell
 -rwxrw-r-- 1 vagrant vagrant    30 Feb 20 00:00 custom_name_shell
 shell:~/root/simple_shell$
 $
```
```bash
 shell:~/root/simple_shell$ echo "pwd" | ./custom_name_shell
 /root/simple_shell
 shell:~/root/simple_shell$
 $
```

```bash
 shell:~/root/simple_shell$ echo "exit 7" | ./custom_name_shell
 shell:~/root/simple_shell$ echo $?
 shell:~/root/simple_shell$ 7
```

-----
## FILES

Help_files: Directory containing help files of built-in commands.

| File | Description  |
| ------- | --- |
| shell.h | Declaration of all functions ande include of libraries|
| main.c | Main file with function to start: <br> - main() <br> - initialize()  |
| basic_fun_1.c | Function to handle commands and errors: <br> handle_path() <br> _getptr() <br> _getoken()  <br> _execute() <br> manage_command()  |
| basic_fun_2.c | Functions to support basic functions: <br> dic_command() <br> error_msg() <br> strtok_line() <br> strtok_path()  |
| aux_fun_1.c | Auxiliar functions: <br> _strlen() <br> _strcat() <br> _strcmp() <br> _strdup() <br> strcpy() |
| aux_fun_2.c | Auxiliar functions: <br> clear_path() <br> atoi() <br> itoa() <br> c_buf() |
| built_func_1.c | Built-in functions: <br> comm_cd() <br> comm_he() <br> comm_ex() <br> comm_en() |
| built_func_2.c | Built-in functions: <br> comm_unset() <br> comm_set() |
| env_fun | Functions to handle environment variables: <br> set_env_v() <br> clear_env() <br> set_env() <br> get_env() |

## Authors
- John Garcia  [@jgarcia15121982](https://www.github.com/jgarcia15121982)
- Anderson Castiblanco [@andergcp](https://www.github.com/andergcp)
- Alejandro Castiblanco [@AlejoCasti](https://www.github.com/AlejoCasti)
