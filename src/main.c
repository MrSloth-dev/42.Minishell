/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:04:52 by joao-pol          #+#    #+#             */
/*   Updated: 2024/10/25 13:16:57 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"

int	g_rec_signal;

void	ft_print_data(t_shell *sh, int is_to_print);

int	ft_check_if_need_to_split_spaces(char *str)
{
	int	i;
	int	have_spaces;

	i = 0;
	have_spaces = FALSE;
	while (str[i])
	{
		if (ft_is_space(str[i]) == TRUE && str[i + 1])
			have_spaces = TRUE;
		if (have_spaces == TRUE)
		{
			i--;
			while (str[++i])
				if (ft_is_space(str[i]) == TRUE)
					str[i] = 32;
			if (i > 0 && !str[i] && str[i - 1] == 32)
				str[i - 1] = '\t';
			i--;
		}
		i++;
	}
	return (have_spaces);
}

void	ft_split_this_node(t_iter *out)
{
	t_iter	in;

	in = ft_set_iter(0);
	if (!out || !out->cur || !out->cur->content)
		return ;
	in.new_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!in.new_lst)
		return ;
	in.front = out->cur->front;
	in.back = out->cur->back;
	in.split = ft_split(out->cur->content, 32);
	if (!in.split)
	{
		ft_free(in.new_lst);
		return ;
	}
	while (in.split[in.i] != NULL)
		in.i++;
	if (in.i == 0)
	{
		ft_free_envp(in.split);
		ft_free(in.new_lst);
		return ;
	}
	in.i++;
	while (in.i > 0)
	{
		if (in.i % 2 == 1)
			ft_append_node(in.new_lst, in.split[in.j++], WORD, NORMAL);
		else
			ft_append_node(in.new_lst, ft_strdup(" "), WHITE_SPACE, NORMAL);
		in.i--;
	}

	out->cur->content = ft_free(out->cur->content);
	out->cur = ft_free(out->cur);
	out->cur = in.new_lst->first;
	
	in.cur_right = out->cur;
	while (in.cur_right->front)
		in.cur_right = in.cur_right->front; //

	out->cur->back = in.back;
	if (in.back)
		in.back->front = out->cur;

	in.cur_right->front = in.front;
	if (in.front)
		in.front->back = in.cur_right;

	while (out->cur != in.cur_right)
		out->cur = out->cur->front;

	ft_free(in.new_lst);
	ft_free(in.split);
}

void	ft_split_tokens_with_white_spaces(t_shell *sh)
{
	t_iter	s;
	int		need_to_split;

	if (!sh || !sh->token_lst || !sh->token_lst->first)
		return;
	s.cur = sh->token_lst->first;
	while (s.cur)
	{
		need_to_split = FALSE;
		if (s.cur->type == WORD && s.cur->status == NORMAL)
			need_to_split = ft_check_if_need_to_split_spaces(s.cur->content);
		if (need_to_split == TRUE)
			ft_split_this_node(&s);
		s.cur = s.cur->front;
	}

}

void	ft_tokenizer(t_token_lst *token_lst, char *line, t_shell *sh)
{
	ft_create_tokens(token_lst, line);

	//ft_print_data(sh, PRINT_DATA);

	ft_join_heredoc_to_words(token_lst);

	//ft_print_data(sh, PRINT_DATA);
	ft_make_expansions(sh);

	ft_split_tokens_with_white_spaces(sh);

	ft_delete_null_expansions_if_needed(sh); //comment for test

	ft_add_node_exec(token_lst, sh); // WAS AFTER DELETE SPACES BEFORE

	ft_convert_empty_strings(sh->token_lst->first); // comment for test
	
	ft_join_tokens(token_lst);



	ft_delete_spaces(token_lst, sh);
	g_rec_signal = 0;
}

void	ft_shellfault(t_shell *sh)
{
	int		exit_status;

	if (!sh || !sh->line || sh->line[0] == 0)
		return ;
	sh->token_lst = ft_calloc(sizeof(t_token_lst), 1);
	if (!sh->token_lst)
		return ;
	ft_tokenizer(sh->token_lst, sh->line, sh);



	ft_check_ambiguous_redir(sh->token_lst->first, sh);


////////////////////////////////////////////////////////////////////////	
	sh->head = ft_make_bin_tree(sh->token_lst->first);
	ft_do_heredoc_files(sh->token_lst->first, sh);
	ft_run_heredocs(sh->token_lst->first, sh);
	ft_print_data(sh, PRINT_DATA);
	ft_print_ambiguous_redir_msg(sh);
//sh->head = NULL;	

	if (sh->head && sh->head->type != ND_PIPE
		&& sh->head->left && ft_isbuiltin(sh->head->left->content))
		ft_exec_builtins_parent(sh->head, sh);
	else if (sh->head && sh->head->left)
	{
		if (fork() == 0)
		{
			ft_sig_restore();
			ft_run(sh->head, sh);
		}
		ft_sig_mute();
		waitpid(0, &exit_status, 0);
		ft_sig_restore();
		sh->exit_status = ft_get_exit_status(exit_status, sh);
	}
	ft_clean_hd_files(sh);
	ft_free_tokens(sh);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*sh;
	int		have_syn_error;

	(void)argc;
	//envp = NULL;
	sh = ft_init_shell(envp, argv[0]);
	while (1)
	{
		ft_readline(sh);
		have_syn_error = ft_have_syntax_error(sh);
		if (have_syn_error != FALSE)
			ft_print_syntax_error(have_syn_error, sh);
		else
			ft_shellfault(sh);
	}
	return (0);
}

char	*ft_print_exec(t_token *cur, char *spaces, int fd)
{
	t_token	*cmd;
	t_token	*rdir;
	char	*left_free;
	char	*right_free;
	int		i;

	i = 0;
	left_free = NULL;
	right_free = NULL;
	cmd = NULL;
	rdir = NULL;
	if (cur && cur->type != ND_PIPE)
	{
		cmd = cur->left;
		rdir = cur->right;
		ft_printf(fd, "%s____________ND_EXEC______________\n", spaces);
	}
	while (cmd || rdir)
	{
		ft_printf(fd, "%s", spaces);
		if (cmd)
		{
			ft_printf(fd,"%s%s ",GREEN, cmd->content);
			cmd = cmd->next;
		}
		else
			ft_printf(fd, "             ");
		if (rdir)
		{
			ft_printf(fd, "  %s%s%s %d", YELLOW, rdir->content, RED, rdir->type);
			rdir = rdir->next;
		}
		ft_printf(fd, "%s\n", RESET);
	}
	if (cur && cur->type == ND_PIPE)
	{
		if ((ft_strlen(spaces) / 2) > 0)
			i = ft_strlen(spaces) / 2;
		if (i == 0)
			ft_printf(fd, "\n                         %sND_PIPE%s \n\n",  RED, RESET );
		else
			ft_printf(fd, "\n%s%s%s%s%s%s%s         ND_PIPE%s \n\n", spaces , spaces + i , spaces + i , spaces + i, spaces + i, spaces + i,  RED, RESET );
		left_free = ft_print_exec(cur->left, ft_strjoin_free(ft_strdup(spaces), ft_strdup(spaces)), fd);
		if (cur->right->right)
			right_free = ft_print_exec(cur->right, ft_strjoin_free(ft_strdup(spaces) , ft_strdup("       ")), fd);
		else
			right_free = ft_print_exec(cur->right, ft_strjoin_free(ft_strdup(spaces) , ft_strdup(" \
		                                                    ")), fd);
		free(left_free);
		free(right_free);
//		ft_print_exec(cur->left, "");
//		ft_print_exec(cur->right,   "                 ");
	}
	return (spaces);
}

void	ft_print_binary_tree(t_shell *sh)
{
	t_token	*cur;
	char	*to_free;
	int		fd; //= open("cmdlog.txt", O_RDWR | O_CREAT | O_APPEND, 0644);

	fd = 1;
	to_free = NULL;
	if (!sh->head)
	{
		ft_printf(2, "NO TREE TO PRINT!\n");
		return ;
	}
	cur = sh->head;
	to_free = ft_print_exec(cur, ft_strdup(""), fd);
	if (to_free)
		free(to_free);
	//close(fd);
}

void	ft_print_tokens(t_token_lst *token_lst)
{
	t_token	*cur;
	t_token *tmp;

	if (!token_lst->first)
		return;
	tmp = token_lst->first;

	ft_printf(1, "%s\n", tmp->content);
	ft_printf(2, "\ncommand: ");
	while (tmp)
	{
		cur = tmp;
		tmp = tmp->front;
		if (cur->type == ND_PIPE)
		{
			ft_printf(2, " | ");
			continue ;
		}
		else if (cur->type == HERE_DOC)
			ft_printf(2, " << ");
		else if (cur->type == REDIR_IN)
			ft_printf(2, " < ");
		else if (cur->type == REDIR_OUT)
			ft_printf(2, " > ");
		else if (cur->type == DBLE_REDIR_OUT)
			ft_printf(2, " >> ");
		else if (cur->type == WHITE_SPACE)
			ft_printf(2, " _ ");
		ft_printf(2, "%s", cur->content);
	}
	cur = token_lst->first;
	ft_printf(2, "\ntypes: ");
	while (cur)
	{
		if (cur->type == WORD)
			ft_printf(2, "WORD ");
		else if (cur->type == ND_EXEC)
			ft_printf(2, "ND_EXEC ");
		else if (cur->type == ND_PIPE)
			ft_printf(2, "PIPE ");
		else if (cur->type == HERE_DOC)
			ft_printf(2, "H_DOC ");
		else if (cur->type == REDIR_OUT)
			ft_printf(2, "R_OUT ");
		else if (cur->type == REDIR_IN)
			ft_printf(2, "R_IN ");
		else if (cur->type == DBLE_REDIR_OUT)
			ft_printf(2, "D_R_OUT ");
		else if (cur->type == WHITE_SPACE)
			ft_printf(2, " WS ");
		else
			ft_printf(2, " OTHER");
		cur = cur->front;
	}
	 printf("\n\n");
}

void	ft_print_data(t_shell *sh, int is_to_print)
{
	if (is_to_print == FALSE)
		return ;
	ft_print_tokens(sh->token_lst); // SEE TOKEN LINKED LIST
	ft_print_binary_tree(sh);  // SEE BIN TREE
}
