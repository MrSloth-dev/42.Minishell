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
		ft_printf(fd, "%s______________________________\n", spaces);
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
			ft_printf(fd, "\n                         %sPIPE%s \n\n",  RED, RESET );
		else
			ft_printf(fd, "\n%s%s%s%s%s%s%s         PIPE%s \n\n", spaces , spaces + i , spaces + i , spaces + i, spaces + i, spaces + i,  RED, RESET );
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

void	ft_print_binary_tree(t_token_lst *token_lst)
{
	t_token	*cur;
	char	*to_free;
	int		fd; //= open("cmdlog.txt", O_RDWR | O_CREAT | O_APPEND, 0644);

	fd = 1;
	to_free = NULL;
	if (!token_lst && !token_lst->first)
	{
		printf("NO TREE TO PRINT!\n");
		return ;
	}
	cur = token_lst->first;
	to_free = ft_print_exec(cur, ft_strdup(""), fd);
	if (to_free)
		free(to_free);
	//close(fd);
}

void	ft_print_tokens(t_token_lst *token_lst)
{
	t_token	*cur;

	if (!token_lst->first)
		return;
	cur = token_lst->first;
	printf("\ncommand: ");
	while (cur)
	{
		if (cur->type == PIPE)
			printf(" ");
		else if (cur->type == HERE_DOC)
			printf(" << ");
		else if (cur->type == REDIR_IN)
			printf(" < ");
		else if (cur->type == REDIR_OUT)
			printf(" > ");
		else if (cur->type == DBLE_REDIR_OUT)
			printf(" >> ");

		printf("%s", cur->content);
		if (cur->type == PIPE)
			printf(" ");
		cur = cur->next;
	}
	cur = token_lst->first;
	printf("\ntypes: ");
	while (cur)
	{
		if (cur->type == WORD)
			printf("WORD ");
		else if (cur->type == WHITE_SPACE)
			printf("ws ");
		else if (cur->type == PIPELINE)
			printf("PIPE ");
		else if (cur->type == HERE_DOC)
			printf("H_DOC ");
		else if (cur->type == REDIR_OUT)
			printf("R_OUT ");
		else if (cur->type == REDIR_IN)
			printf("R_IN ");
		else if (cur->type == DBLE_REDIR_OUT)
			printf("D_R_OUT ");
		else if (cur->type == SINGLE_QTE)
			printf("s_qt ");
		else if (cur->type == DOUBLE_QTE)
			printf("D_qt ");
		else if (cur->type == ENV)
			printf("ENV ");
		cur = cur->next;
	}
//	printf("\n");
	// cur = token_lst->first;
	// printf("STATUS: ");
	// while (cur)
	// {
	// 	if (cur->status == NORMAL)
	// 		printf("normal ");
	// 	else if (cur->status == IN_DOUBLE_QTE)
	// 		printf("in_DOUBLE_qte ");
	// 	else if (cur->status == IN_SINGLE_QTE)
	// 		printf("in_SINGLE_qte ");
	// 	cur = cur->next;
	// }
	 printf("\n\n");
}
