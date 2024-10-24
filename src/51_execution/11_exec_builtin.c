#include "minishell.h"

void	ft_exec_builtins(t_token *temp_head, t_shell *shell)
{
	t_token	*temp_next;

	temp_next = NULL;
	if (temp_head && temp_head->next)
	{
		temp_next = temp_head->next;
		temp_next->prev = NULL;
	}
		if (ft_strcmp(temp_head->content, "cd") == 0)
			ft_cd(temp_next, shell);
		else if (ft_strcmp(temp_head->content, "env") == 0)
			ft_env(shell);
		else if (ft_strcmp(temp_head->content, "pwd") == 0)
			ft_pwd(shell);
		else if (ft_strcmp(temp_head->content, "echo") == 0)
			ft_echo(temp_next, shell);
		else if (ft_strcmp(temp_head->content, "export") == 0)
			ft_export(temp_next, shell);
		else if (ft_strcmp(temp_head->content, "unset") == 0)
			ft_unset(temp_next, shell);
		else if (ft_strcmp(temp_head->content, "exit") == 0)
			ft_exit(temp_next, shell);
}

void	ft_exec_builtins_child(t_token *cmdargs, t_shell *sh)
{
	if (cmdargs)
		ft_exec_builtins(cmdargs->left, sh);
	ft_free_and_exit(NULL, sh, TRUE);
}

void	ft_restore_fd(int std_in, int std_out, t_shell *sh)
{
	sh->exit_status = 1;
	dup2(std_out, STDOUT_FILENO);
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	close(std_out);
}

void	ft_exec_builtins_parent(t_token *cmdargs, t_shell *sh)
{
	int		fd;
	int		std_out;
	int		std_in;

	fd = 420;
	if (cmdargs->right)
	{
		std_out = dup(STDOUT_FILENO);
		std_in = dup(STDIN_FILENO);
		fd = ft_exec_redir(cmdargs->right, sh);
	}
	if (fd != -1)
	{
		ft_exec_builtins(cmdargs->left, sh);
		if (cmdargs->right)
			ft_restore_fd(std_in, std_out, sh);
		// close(fd);
	}
	if (cmdargs->right)
	{
		close(std_in);
		close(std_out);
	}
}
