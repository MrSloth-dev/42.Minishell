#include "minishell.h"

int	ft_is_word(char c)
{
	if (!c)
		return (FALSE);
	if (c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '$'
		|| c == '"'
		|| c == '\''
		|| ft_is_space(c) == TRUE)
		return (FALSE);
	else
		return (TRUE);
}

int	ft_how_much_consecutives_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_space(str[i]) == TRUE)
		i++;
	return (i);
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
