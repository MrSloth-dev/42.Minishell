# ShellFault

## Possivelment o pior e mais incompleto projecto (ainda)

[Subject](https://cdn.intra.42.fr/pdf/pdf/138331/en.subject.pdf)
### Dictionary of Allowed Functions

### Some references
https://github.com/tasmanday/42_minishell<br>
https://github.com/josephcheel/42-Minishell<br>
https://github.com/Kuninoto/42_minishell<br>
https://github.com/marcelofassbinder/42_MINISHELL (added 30/08 | user mfassbin)<br>

#### TODO Organize and add a definition
//-------readline fts--------//
- readline ----->>> see 00_readline, on z_i_std 
- rl_clear_history ----->>> apparently not necessary  - need check on other projects
- rl_on_new_line ----->>> 02_rl_on_new_line - implemented signals - test ctrl + C, ctrl + D, and ignore ctrl + \
- rl_replace_line - Replace current line ----->>> 02_rl_on_new_line implemented here 
- rl_redisplay - redisplay modified line ----->>> 02_rl_on_new_line implemented here
- add_history - add to previous commands ----->>> 06_add_history lines 40 and 41 - simple as that!
- //-------print fts and memory management----//
- printf - prints on stdout
- malloc - simple allocation of memory, will be used in variables, history
- free - soltem os prisioneiros de todo o mundo 
- write - print in which fd we desire, will be useful to print in stdin (make interactive??)
- access - check if there is acess( for checking executing command binaries)
- open - open file descriptor returns an int or -1 if invalid
- read - read from file descriptor returns number of bytes read, -1 if invalid
- close - close the file descriptor
- fork - create a child process, return the pid of the child, when in child process pid is 0
- wait - wait for children
- waitpid - wait for children with certain pid ----->>> 16_wait
- wait3
- wait4
- signal (isilva - see 02_rl_on_new_line, used to ignire SIGQUIT on ctrl + \ comination)
- sigaction (isilva-t - see 02_rl_on_new_line implementation)
- sigemptyset (isilva-t understand)
- sigaddset (isilva-t understand)
- kill (isilva-t understand)
- exit - exit the program, need to free memory before (isilva-t - its a interruption of the program, in other ft than main ft)
- 
- getcwd
- chdir
- stat
- lstat
- fstat
- unlink - remove?
- execve - execute other binaries
- dup - duplicate the file descriptor
- dup2 - rewrite the file descritor for another, used in redirection
- pipe - create a channel of communication between file descritors.
- opendir
- readdir
- closedir
- strerror
- perror
- isatty
- ttyname
- ttyslot
- ioctl,
- getenv
- tcsetattr
- tcgetattr
- tgetent
- tgetflag
- tgetnum
- tgetstr
- tgoto
- tputs

### Features to Implement
- [ ] Display a prompt when waiting for a new command;
- [ ] Have a Working History (up and down keys must show commands , ctrl + r search commands, and after show command, we can edit command)
- [ ] Search and launch the right executable(based on PATH relative or absolute)
- [ ] Avoid using more than one global variable
- [ ] Not interpret unclosed quotes
- [ ] Handle ' to prevent shell from intrepeting the meta characters in the quoted sequence
- [ ] Handle " wich shoudl prevent the shell from interpreting the meta-characters in the quoted sequence except for $
- [ ] Implement redirections : < > << >> 
- [ ] Implement pipes |
- [ ] Handle environment variables ($ followed by a sequence of characters) should expand
- [ ] Handle $? wich should expand exit status of the most recently executed foreground pipeline
- [ ] Handle ctrl -C, ctrl -D and ctrl -\ which should behave like in bash (ready 02_rl_on_newline isilva-t)
- [ ] In Interactive mode:
    - [ ] ctrl-C display a new prompt on a new line. (ready 02_rl_on_newline isilva-t - handled by sigaction)
    - [ ] ctrl-D exits the shell (ready 02_rl_on_newline isilva-t - handled by readline itself, wich readline receives EOF)
    - [ ] ctr-\ does nothing (ready 02_rl_on_newline isilva-t, but needs to check if need change value on global variable)
- [ ] Implement BUILT-INS:
 - [ ] echo with -n
 - [ ] cd with only a relative or absoute path (no fucking cd ~)
 - [ ] pwd with no options
 - [ ] export with no options
 - [ ] unset with no options
 - [ ] env with no option or aguments
 - [ ] exit with no options

# Ivan needs to understand:
- [ ] Implement redirections : < > << >> 

