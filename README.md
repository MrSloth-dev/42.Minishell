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
readline - ivan say: see 00_readline, on z_i_std, <br>
rl_clear_history - ivan say: apparently not necessary, cause  - need check on other projects<br>
rl_on_new_line
rl_replace_line
rl_redisplay
add_history
printf
malloc
free
write
access
open
read
close
fork
wait
waitpid
wait3
wait4
signal
sigaction
sigemptyset
sigaddset
kill
exit
getcwd
chdir
stat
lstat
fstat
unlink
execve
dup
dup2
pipe
opendir
readdir
closedir
strerror
perror
isatty
ttyname
ttyslot
ioctl,
getenv
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs
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
- [ ] Handle ctrl -C, ctrl -D and ctrl -\ which should behave like in bash
- [ ] In Interactive mode:
    - [ ] ctrl-C display a new prompt on a new line.
    - [ ] ctrl-D exits the shell
    - [ ] ctr-\ does nothing
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

