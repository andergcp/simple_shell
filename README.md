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
 git clone https://github.com/andergcp/simple_shell.git
```

2. Compile all files to get executable file

```bash
 gcc *.c -o custom_name_shell
```

3. Execute 

```bash
 ./custom_name_shell
```

-----
## USAGE

### INTERACTIVE MODE

Interactive mode allows you to enter as many commands as you want.
Also allows you to exit in two ways, press ```CTRL + D``` or 
exit built-in command. ```$ exit ```

To run simple shell just execute the command below

```bash
 ./custom_name_shell
```

It will display this screen that means you are inside
This is the prompt
```bash
 $ 
```
```bash
 $ echo test
 test
 $ 
```

### NON INTERACTIVE MODE

Non interactive mode allows you to run a simple command.

```bash
 echo "command to run" | ./custom_name_shell
```

```bash
 echo "ls -l" | ./custom_name_shell
 -rwxrw-r-- 1 vagrant vagrant    29 Apr 16 18:22 custom_name_shell
```

-----
## BUILT-IN COMMANDS

More information about each command use help. ```$ help built-in_command```


```bash
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
