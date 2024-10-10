/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:06:02 by joao-pol          #+#    #+#             */
/*   Updated: 2024/07/19 15:52:02 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error_msg(char *error_msg, int ERRNO)
{
	perror(error_msg);
	if (ERRNO != SUCCESS)
		exit(ERRNO);
	return (ERRNO);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		ft_error_msg("Error with command", EXECVE_ERROR_CHILD);
}

void	ft_free_files(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	while (pipex->cmd_paths[i])
		free(pipex->cmd_paths[i++]);
	free(pipex->cmd_paths);
}

void	*ft_free(char **str, size_t index)
{
	size_t	j;

	j = 0;
	while (j++ < index)
		free(str[j]);
	free(*str);
	return (NULL);
}
