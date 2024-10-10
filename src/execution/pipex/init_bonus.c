/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:07:21 by joao-pol          #+#    #+#             */
/*   Updated: 2024/07/19 15:37:18 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_init_pipex(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	pipex->env = envp;
	pipex->here_doc = 0;
	pipex->limiter = NULL;
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->find_path = ft_find_path(envp);
	pipex->cmd_paths = ft_split(pipex->find_path, ':');
	if (!pipex->cmd_paths)
		exit (ft_error_msg("Error with cmd_paths allocation ", MEMORY_ERROR));
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
	int	len;

	len = ft_strlen(delimiter);
	while(1)
	{
		ft_putstr_fd("here_doc> ", 1);
		temp = get_next_line(STDIN_FILENO);
		if (ft_strncmp(delimiter, temp, len) == 0
		&& temp[len] == '\n')
		{
			free(temp);
			close(0);
			close(1);
			close(fd[1]);
			temp = get_next_line(STDIN_FILENO);
			break ;
		}
		ft_putstr_fd(temp, fd[1]);
		free(temp);
	}
	free(temp);
	temp = NULL;
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
		ft_here_doc(pipex->pipe[0], pipex->limiter);
	else
		pipex->pipe[0][0] = pipex->infile;
	i = 0;
	while (i < pipex->cmd_count  - 1)
	{
		pipex->pipe[i][1] = pipex->pipe[i + 1][1];
		i++;
	}
	pipex->pipe[pipex->cmd_count - 1][1] = pipex->outfile;
	return (SUCCESS);


}

