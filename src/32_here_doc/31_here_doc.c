/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:04:37 by isilva-t          #+#    #+#             */
/*   Updated: 2024/10/25 10:12:03 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc(char *prog_name, char *delimiter, int hd_id, char *file)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		hd_id = open(file, O_RDWR | O_APPEND, 0644);
		if (line == NULL)
		{
			ft_printf(1, "%s: warning: here-document delimited ", prog_name);
			ft_printf(1, "by end-of-file (wanted `%s')\n", delimiter);
			return (close(hd_id), 0);
		}
		else if (ft_strcmp(line, delimiter) == 0)
			return (close(hd_id), 0);
		else if ((line || *(line)))
		{
			ft_printf(hd_id, "%s", line);
			write(hd_id, "\n", 1);
			close(hd_id);
		}
		line = ft_free(line);
	}
}

static void	ft_free_inside_heredoc(t_shell *sh)
{
	if (!sh)
		return ;
	sh->line = ft_free(sh->line);
	ft_free_tokens(sh);
	sh->token_lst = ft_free(sh->token_lst);
	if (sh->envp)
		sh->envp = ft_free_envp(sh->envp);
	if (sh->path)
		sh->path = ft_free_envp(sh->path);
	sh->hd_path = ft_free(sh->hd_path);
	sh = ft_free(sh);
}

static void	ft_get_vars_for_this_hd(t_iter *s, char *delimiter, char *file)
{
	ft_bzero(delimiter, 4096);
	s->i = ft_strlen(s->cur->content) + 1;
	if (s->i >= 4095)
		s->i = 4094;
	ft_strlcpy(delimiter, s->cur->content, s->i);
	s->i = 0;
	ft_bzero(file, 256);
	s->j = ft_strlen(s->cur->file) + 1;
	if (s->j >= 255)
		s->j = 254;
	ft_strlcpy(file, s->cur->file, s->j);
	s->j = 0;
}

static void	ft_init_hd_vars(t_iter *s, char	*prog_name,
							t_token *token, t_shell *sh)
{
	s->cur = token;
	ft_bzero(prog_name, 256);
	s->k = ft_strlen(sh->prog_name) + 1;
	ft_strlcpy(prog_name, sh->prog_name, s->k);
	prog_name[254] = 0;
	s->k = 0;
}

void	ft_run_heredocs(t_token *token, t_shell *sh)
{
	t_iter	s;
	int		status;
	char	delimiter[4096];
	char	prog_name[256];
	char	file[256];

	if (!token || !sh)
		return ;
	s = ft_set_iter(0);
	ft_init_hd_vars(&s, prog_name, token, sh);
	while (s.cur)
	{
		if (s.cur->file)
		{
			ft_get_vars_for_this_hd(&s, delimiter, file);
			s.pid = fork();
			if (s.pid == 0)
			{
				ft_sig_child();
				ft_free_inside_heredoc(sh);
				ft_here_doc(prog_name, delimiter, s.fd, file);
				exit (0);
			}
			else
			{
				ft_sig_mute();
				waitpid(s.pid, &status, 0);
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				{
					ft_printf(1, "\n");
					sh->head = NULL;
					sh->exit_status = 130;
					ft_sig_restore();
					break ;
				}
			}
		}
		s.cur = s.cur->front;
	}
	ft_sig_restore();
}

void	ft_create_and_run_heredocs(t_shell *sh)
{
	if (sh->nb_heredoc < 1)
		return ;
	ft_run_heredocs(sh->token_lst->first, sh);
}
