# ShellFault


## Possivelment o pior e mais incompleto projecto (ainda)

[Subject](https://cdn.intra.42.fr/pdf/pdf/138331/en.subject.pdf)
### Dictionary of Allowed Functions

### Some references
- https://github.com/tasmanday/42_minishell
- https://github.com/josephcheel/42-Minishell
- https://github.com/Kuninoto/42_minishell
- https://github.com/marcelofassbinder/42_MINISHELL (added 30/08 | user mfassbin)

#### TODO Organize and add a definition
//-------readline fts--------//
- readline ----->>> see 00_readline, on z_i_std 
- rl_clear_history ----->>> maybe use in free FT for "good practices"
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
- fork - create a child process, return the pid of the child, when in child process pid is 0 ----->>> 15_fork
- wait - wait for children ----->>> 16_wait_*
- waitpid - wait for children with certain pid ----->>> 16_wait
- wait3 ----->>> apparently not necessary
- wait4 ----->>> apparently not necessary
- signal (isilva - see 02_rl_on_new_line, used to ignire SIGQUIT on ctrl + \ comination)
- sigaction (isilva-t - see 02_rl_on_new_line implementation)
- sigemptyset (isilva-t understand)
- sigaddset (isilva-t understand)
- kill (isilva-t understand)
- exit - exit the program, need to free memory before (isilva-t - its a interruption of the program, in other ft than main ft)
- getcwd - return char* of current directory. Need to alocate buffer for string --->>> 21_getcwd
- chdir - function returns 0 on sucess, and -1 if directory doesent exist --->>> 22_chdir
- stat --->>> tested but maybe not necessary
- lstat NO
- fstat NO
- unlink - remove heredocs
- execve - execute other binaries --->>> 31_execve
- dup - duplicate the file descriptor
- dup2 - rewrite the file descritor for another, used in redirection --->>>> 32_dup2_and_pipe BUT NEED UNDERSTAND!
- pipe - create a channel of communication between file descritors.
- opendir 
- readdir
- closedir
- perror
- getenv
### Not Used Commands 
- strerror NO
- isatty NO
- ttyname NO
- ttyslot NO
- ioctl, NO
- tcsetattr NO
- tcgetattr NO
- tgetent NO
- tgetflag NO
- tgetnum NO
- tgetstr NO
- tgoto NO
- tputs NO

### Features to Implement
- [x] Display a prompt when waiting for a new command;
- [x] Have a Working History (up and down keys must show commands , ctrl + r search commands, and after show command, we can edit command)
- [x] Search and launch the right executable(based on PATH relative or absolute)
- [x] Avoid using more than one global variable
- [x] Not interpret unclosed quotes
- [x] Handle ' to prevent shell from intrepeting the meta characters in the quoted sequence
- [x] Handle " wich shoudl prevent the shell from interpreting the meta-characters in the quoted sequence except for $
- [x] Implement redirections : < > << >> 
   - [x] <
   - [x] >
   - [x] >>
   - [x] Need to fix redirections on builtin parents, for some reasons it's fucking with signals it kinda works?
   - [x] << HERE DOC
      - [x] SIMPLE
      - [x] MULTIPLE
      - [x] heredoc exansions //will not be done
      - [x] heredoc fucking work
      - [x] working with signal Ctrl+c Ctrl + d
      - [x] NO FUCKING EXPANSIONS when have spaces befor quotes on heredoc!!!!!
- [x] Implement pipes |
- [x] EXPANDER :
   - [x] Handle environment variables ($ followed by a sequence of characters) should expand
   - [x] Handle $? wich should expand exit status of the most recently executed foreground pipeline
- [x] Handle ctrl -C, ctrl -D and ctrl -\ which should behave like in bash (ready 02_rl_on_newline isilva-t)
- [x] In Interactive mode:
    - [x] ctrl-C display a new prompt on a new line. (ready 02_rl_on_newline isilva-t - handled by sigaction)
    - [x] ctrl-D exits the shell (ready 02_rl_on_newline isilva-t - handled by readline itself, wich readline receives EOF)
    - [x] ctr-\ does nothing (ready 02_rl_on_newline isilva-t, but needs to check if need change value on global variable)
- [x] Implement BUILT-INS:
 - [x] echo with -n
    - [x] check for leaks
    - [x] Works
    - [x] convert to accept tokens
 - [x] pwd with no options
    - [x] check for leaks
    - [x] convert to accept tokens
 - [x] env with no option or aguments
   
    - [x] convert to accept tokens
    - [x] check for leaks
 - [x] export with no options
    - [x] If multiple variable to export and one of them has an error
    - [x] Make sure name doesnt contain invalid identifiers
    - [x] prints with "declare -x" with 0 args
    - [x] Append non existant env_var
    - [x] Swap existant env_var
    - [x] Join with '+' existant env_var
    - [x] Fucking Works
    - [x] convert to accept tokens
    - [x] check for leaks
 - [x] unset with no options
    - [x] Fucking Works
    - [x] convert to accept tokens
    - [x] check for leaks
 - [x] cd with only a relative or absoute path (no fucking cd ~) need readline to test
    - [x] cd with relative path
    - [x] cd with absolute path
    - [x] cd - goes to OLDPWD
    - [x] cd -- goes to home and set oldpwd to home too)
    - [ ] cd ~ goes to HOME of the system
    - [x] cd goes to HOME
    - [x] convert to accept tokens
    - [x] check for leaks
 - [x] exit with no options (this shiet has signals)
   - [x] it exits
   - [x] clears memory
 - [ ] Make safe functions
   
 - [ ] TESTS TO SOLVE
   - [x] free on failed execve
   - [x] try pwd -> ENTER -> cat infile -> ENTER -> ctr + d -> LEAKS!
   - [x] more than 2 ENTER without line, have leaks
   - [x] "" | "" is missing addings a ND_EXEC after the pipe
   - [ ] Readline is erasing history
   - [x] Maybe need to handle tabs as whitespaces
   - [ ] NORMINETTE, AMENO, DOMINE, AMENO NORMINETTE
   - [x] handle CTRL + D when use heredoc -> reseted sh->nb_heredoc
   - [x] handle CTRL + C in heredoc
   - [x] verify if have leaks with heredoc
   - [x] use a hidden directory to store files created from heredoc
   - [x] delete heredoc temp files after each execution
   - [ ] verify add history if it's ok - IVAN
   - [x] >>$a|""|''|>$b open fd - ok?
   - [ ] cd "" need to stay put  - JOAO
   - [x] /'' - OK
   - [x] <'<'ec redirect fail from '<ec' OK!
   - [x] export T+T= ok!
   - [x] echo <123 <2456 koo | echo 1 fd open - ok ?
   - [x] | echo oi this error propagates to another erros of invalid read of one empty token
   - [x] "|" echo  oi
   - [x] echo | "|" ok
   - [x] echo |"$?"
   - [x] export UNO=1 DOS-2 TRES=3 | env | grep TRES
   - [x] export | grep - joao
   - [x] joao-pol@c2r5s2:~/CommonCore/3.MiniShell$ < $A IVAN
         bash: $A: ambiguous redirect
   - [ ] Ctrl + \ for child processes that are awaiting IVAN
   - [ ] Test here_doc
   - [ ] cat "" -VER O QUE A MERDA DO BASH DA

```
## Tests to be made

- [ ] `<<end"$USER" > log` ends with `end$USER`
- [ ] ```-n1 hellojoao-pol@c2r6s4:~$ echo -n -nnn -nnn -nnn -n1 "hello"
-n1 hellojoao-pol@c2r6s4:~$```
