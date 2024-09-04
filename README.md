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
//-------readline fts--------//<br>
readline $${\color{red}{see 00_readline, on z_i_std}}$$  <br>
rl_clear_history - (apparently not necessary  - need check on other projects)<br>
rl_on_new_line - (02_rl_on_new_line - implemented signals - test ctrl + C, ctrl + D, and ignore ctrl + \<br>
rl_replace_line - Replace current line (02_rl_on_new_line implemented here) <br>
rl_redisplay - redisplay modified line (02_rl_on_new_line implemented here)<br>
add_history - add to previous commands (06_add_history lines 40 and 41 - simple as that!)<br>
//-------print fts and memory management----//<br>
printf - prints on stdout<br>
malloc - simple allocation of memory, will be used in variables, history<br>
free - soltem os prisioneiros de todo o mundo <br>
write - print in which fd we desire, will be useful to print in stdin (make interactive??)<br>

access - check if there is acess( for checking executing command binaries)<br>
open - open file descriptor returns an int or -1 if invalid<br>
read - read from file descriptor returns number of bytes read, -1 if invalid<br>
close - close the file descriptor<br>
fork - create a child process, return the pid of the child, when in child process pid is 0<br>
wait - wait for children<br>
waitpid - wait for children with certain pid<br>
wait3<br>
wait4<br>

signal (isilva - see 02_rl_on_new_line, used to ignire SIGQUIT on ctrl + \ comination)<br>
sigaction (isilva-t - see 02_rl_on_new_line implementation)<br>
sigemptyset (isilva-t understand)<br>
sigaddset (isilva-t understand)<br>
kill (isilva-t understand)<br>
exit - exit the program, need to free memory before (isilva-t - its a interruption of the program, in other ft than main ft)<br>

getcwd<br>
chdir<br>
stat<br>
lstat<br>
fstat<br>
unlink - remove?<br>
execve - execute other binaries<br>
dup - duplicate the file descriptor<br>
dup2 - rewrite the file descritor for another, used in redirection<br>
pipe - create a channel of communication between file descritors.<br>
opendir<br>
readdir<br>
closedir<br>
strerror<br>
perror<br>
isatty<br>
ttyname<br>
ttyslot<br>
ioctl,<br>
getenv<br>
tcsetattr<br>
tcgetattr<br>
tgetent<br>
tgetflag<br>
tgetnum<br>
tgetstr<br>
tgoto<br>
tputs<br>

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

