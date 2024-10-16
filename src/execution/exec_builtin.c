#include "minishell.h"

void	ft_exec_builtins(t_token *cmdargs, t_shell *shell)
{
	t_token	*temp_next;
	t_token	*temp_head;

	temp_head = cmdargs;
	temp_next = NULL;
	if (temp_head)
	{
		temp_head = temp_head->left;

		if (temp_head && temp_head->next)
		{
			temp_next = temp_head->next;
			temp_next->prev = NULL;
		}
		if (ft_strcmp("cd", temp_head->content) == 0)
			ft_cd(temp_next, shell);
		else if (ft_strcmp("env", temp_head->content) == 0)
			ft_env(shell);
		else if (ft_strcmp("pwd", temp_head->content) == 0)
			ft_pwd(shell);
		else if (ft_strcmp("echo", temp_head->content) == 0)
			ft_echo(temp_next, shell);
		else if (ft_strcmp("export", temp_head->content) == 0)
			ft_export(temp_next, shell);
		else if (ft_strcmp("unset", temp_head->content) == 0)
			ft_unset(temp_next, shell);
		else if (ft_strcmp("exit", temp_head->content) == 0)
			ft_exit(NULL, shell);
	}
	ft_free_and_exit(NULL, shell, TRUE);
}

void	ft_exec_builtins_parent(t_token *cmdargs, t_shell *shell)
{
	t_token	*temp_next;
	t_token	*temp_head;

	temp_head = cmdargs;
	temp_next = NULL;
	if (temp_head)
	{
		temp_head = temp_head->left;
		if (temp_head && temp_head->next)
		{
			temp_next = temp_head->next;
			temp_next->prev = NULL;
		}
		if (ft_strcmp("cd", temp_head->content) == 0)
			ft_cd(temp_next, shell);
		else if (ft_strcmp("env", temp_head->content) == 0)
			ft_env(shell);
		else if (ft_strcmp("pwd", temp_head->content) == 0)
			ft_pwd(shell);
		else if (ft_strcmp("echo", temp_head->content) == 0)
			ft_echo(temp_next, shell);
		else if (ft_strcmp("export", temp_head->content) == 0)
			ft_export(temp_next, shell);
		else if (ft_strcmp("unset", temp_head->content) == 0)
			ft_unset(temp_next, shell);
		else if (ft_strcmp("exit", temp_head->content) == 0)
			ft_exit(NULL, shell);
	}
}
