# ShellFault

## Possivelment o pior e mais incompleto projecto (ainda)

[Subject](https://cdn.intra.42.fr/pdf/pdf/138331/en.subject.pdf)
### Dictionary of Allowed Functions

#### TODO Organize and add a definition
readline
rl_clear_history
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
- [ ] Have a Working Directory (pwd)
- [ ] Search and launch the right executable(based on PATH relative or absolute)
- [ ] Avoid using more than one global variable
- [ ] Not interpret unclosed quotes
- [ ] Handle ' to prevent shell from intrepeting the meta characters in the quoted sequence
- [ ] Handle " wich shoudl prevent the shell from interpreting the meta-characters in the quoted sequence except for $
- [ ] Implement redirections : < > << >>
- [ ] Implement pipes |
- [ ] Handle environment variables ($ followed by a sequence of characters) should expand
- [ ] Handle $? wich should expand exit status of the most recently executed foreground pipeline
