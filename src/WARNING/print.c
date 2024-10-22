#include "minishell.h"
#include <fcntl.h>

static char	*ft_print_exec(t_token *cur, char *spaces, int fd)
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
		printf("NO TREE TO PRINT!\n");
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
	printf("\ncommand: ");
	while (tmp)
	{
		cur = tmp;
		tmp = tmp->front;
		if (cur->type == ND_PIPE)
		{
			printf(" | ");
			continue ;
		}
		else if (cur->type == HERE_DOC)
			printf(" << ");
		else if (cur->type == REDIR_IN)
			printf(" < ");
		else if (cur->type == REDIR_OUT)
			printf(" > ");
		else if (cur->type == DBLE_REDIR_OUT)
			printf(" >> ");
		printf("%s", cur->content);
	}
	cur = token_lst->first;
	printf("\ntypes: ");
	while (cur)
	{
		if (cur->type == WORD)
			printf("WORD ");
		else if (cur->type == ND_EXEC)
			printf("ND_EXEC ");
		else if (cur->type == ND_PIPE)
			printf("PIPE ");
		else if (cur->type == HERE_DOC)
			printf("H_DOC ");
		else if (cur->type == REDIR_OUT)
			printf("R_OUT ");
		else if (cur->type == REDIR_IN)
			printf("R_IN ");
		else if (cur->type == DBLE_REDIR_OUT)
			printf("D_R_OUT ");
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
