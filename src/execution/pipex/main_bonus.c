/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:04:52 by joao-pol          #+#    #+#             */
/*   Updated: 2024/07/17 16:24:42 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "ft_printf.h"

//https://excalidraw.com/#json=zNIb-IxgYzBnoW5JdD15h,TMHYz8CAfvyvEfN8DSsbRg
int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < 5)
		return (ft_error_msg("Error with Input", INPUT_ERROR));
	else
	{
		ft_init_pipex(&pipex, argc, argv, envp);
		ft_pipex(&pipex, argc, argv, envp);
		ft_free_files(&pipex);
	}
	return (SUCCESS);
}

int	ft_open_files(t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->outfile = open(pipex->argv[pipex->argc - 1], O_CREAT | O_RDWR | O_APPEND);
	else
		pipex->outfile = open(pipex->argv[pipex->argc - 1], O_CREAT | O_RDWR | O_APPEND);
	if (pipex->outfile == -1)
		ft_error_msg("Error with Outfile ", OUTFILE_ERROR);
	if (!pipex->here_doc)
	{
		pipex->infile = open(pipex->argv[2], O_RDONLY);
		if (pipex->infile == -1)
			ft_error_msg("Error with Infile ", INFILE_ERROR);
	}
	return (SUCCESS);
}

void	ft_here_doc(int *fd, char *delimiter)
{
	char	*temp;
	while(1)
	{
		ft_putstr_fd("here_doc> ", 1);
		temp = get_next_line(STDIN_FILENO);
		if (ft_strncmp(delimiter, temp, ft_strlen(delimiter)) == 0
		&& temp[ft_strlen(delimiter)] == '\n')
			break ;
		ft_putstr_fd(temp, fd[1]);
	}
	close(0);
	close(1);
	free(temp);
}

void	ft_free_pipes(t_pipex *pipex, int i)
{
	while (i >= 0)
	{
		free(pipex->pipe[i]);
		i++;
	}
	free(pipex->pipe);
}

int	ft_create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipe = malloc(sizeof(int) * pipex->cmd_count);
	if (!pipex->pipe)
		return (PIPE_ERROR);
	while (i < pipex->cmd_count)
	{
		pipex->pipe[i] = malloc(sizeof(int) * 2);
		if (pipex->pipe[i] || pipe(pipex->pipe[i]))
		{
			ft_free_pipes(pipex, i);
			ft_msg_error("Error with pipe", PIPE_ERROR);
		}
	}

	return (SUCCESS);
	
}

int	ft_create_pipeline(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->here_doc)


}

int	ft_init_pipex(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	pipex->env = envp;
	pipex->here_doc = 0;
	pipex->limiter = NULL;
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->cmd_count = argc - 3;
	pipex->offset_args = 2;
	pipex->save_state = 0;
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		pipex->here_doc = 1;
		pipex->offset_args = 3;
	}
	ft_open_files(pipex);
	ft_create_pipes(pipex);
	ft_create_pipeline(pipex);
	return (SUCCESS);
}

void	ft_pipex(t_pipex *pipex, char *argv[], char *envp[])
{
	t_pid	pid;

	pid = fork();
	if (pipex->pid1 == -1)
		ft_error_msg("Error with Fork ", FORK_ERROR);
	else if (!pipex->pid1)
	{
		ft_child_process(*pipex, argv, envp);
	}
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
	{
		ft_parent_process(*pipex, argv, envp);
	}
	waitpid(-1, &pipex->save_state, 0);
}

void	ft_child_process(t_pipex pipex, char **argv, char **envp)
{
	if (dup2(pipex.pipe[1], STDOUT_FILENO) == -1)
		ft_error_msg("Error with STDOUT in child", FD_STDOUT_CHILD);
	close(pipex.pipe[0]);
	if (dup2(pipex.infile, STDIN_FILENO) == -1)
		ft_error_msg("Error with STDIN in child", FD_STDIN_CHILD);
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (ft_check_quotes(pipex.cmd_args) == 0)
		ft_error_msg("Error with EXECVE", EXECVE_ERROR_CHILD);
	ft_get_cmd(&pipex);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		ft_error_msg("Error with EXECVE", EXECVE_ERROR_CHILD);
}

void	ft_parent_process(t_pipex pipex, char **argv, char **envp)
{
	if (dup2(pipex.pipe[0], STDIN_FILENO) == -1)
		ft_error_msg("Error with STDOUT in parent", FD_STDOUT_PARENT);
	close(pipex.pipe[1]);
	if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
		ft_error_msg("Error with STDIN in parent", FD_STDIN_PARENT);
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (ft_check_quotes(pipex.cmd_args) == 0)
		ft_error_msg("Error with ", EXECVE_ERROR_CHILD);
	pipex.cmd = pipex.cmd_args[0];
	ft_get_cmd(&pipex);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		ft_error_msg("Error with ", EXECVE_ERROR_PARENT);
}
