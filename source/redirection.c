/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 11:00:59 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 20:18:00 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	redirections(t_cmd *cmd, t_shell *shell)
// {
// 	t_redir	*cur;
// 	int		last_out;
// 	int		last_in;

// 	last_out = -1;
// 	last_in = -1;
// 	cur = cmd->redirs;
// 	while (cur)
// 	{
// 		if (cur->type == REDIR_IN)
// 		{
// 			if (last_in != -1)
// 				close(last_in);
// 			last_in = open(cur->file, O_RDONLY);
// 		}
// 		else if (cur->type == HEREDOC)
// 		{
// 			if (last_in != -1)
// 				close(last_in);
// 			last_in = cur->fd;
// 		}
// 		else if (cur->type == APPEND)
// 		{
// 			if (last_out != -1)
// 				close(last_out);
// 			last_out = open(cur->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		}
// 		else
// 		{
// 			if (last_out != -1)
// 				close(last_out);
// 			last_out = open(cur->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		}
// 		if ((cur->type == REDIR_IN && last_in < 0)
// 			|| (cur->type != REDIR_IN && cur->type != HEREDOC && last_out < 0))
// 			return (print_errors(cur->file, shell, 1), -1);
// 		cur = cur->next;
// 	}
// 	if (last_in != -1)
// 	{
// 		dup2(last_in, STDIN_FILENO);
// 		close(last_in);
// 	}
// 	if (last_out != -1)
// 	{
// 		dup2(last_out, STDOUT_FILENO);
// 		close(last_out);
// 	}
// 	return (0);
// }

static int	open_input(t_redir *redir, int *last_in, t_shell *shell)
{
	if (*last_in != -1)
		close(*last_in);
	if (redir->type == HEREDOC)
		*last_in = redir->fd;
	else
		*last_in = open(redir->file, O_RDONLY);
	if (*last_in < 0)
		return (print_errors(redir->file, shell, 1), -1);
	return (0);
}

static int	open_output(t_redir *redir, int *last_out, t_shell *shell)
{
	int	flags;

	if (*last_out != -1)
		close(*last_out);
	flags = O_WRONLY | O_CREAT;
	if (redir->type == APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	*last_out = open(redir->file, flags, 0644);
	if (*last_out < 0)
		return (print_errors(redir->file, shell, 1), -1);
	return (0);
}

static void	apply_redirections(int last_in, int last_out)
{
	if (last_in != -1)
	{
		dup2(last_in, STDIN_FILENO);
		close(last_in);
	}
	if (last_out != -1)
	{
		dup2(last_out, STDOUT_FILENO);
		close(last_out);
	}
}

int	redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*cur;
	int		last_in;
	int		last_out;

	last_in = -1;
	last_out = -1;
	cur = cmd->redirs;
	while (cur)
	{
		if (cur->type == REDIR_IN || cur->type == HEREDOC)
		{
			if (open_input(cur, &last_in, shell) < 0)
				return (-1);
		}
		else
		{
			if (open_output(cur, &last_out, shell) < 0)
				return (-1);
		}
		cur = cur->next;
	}
	apply_redirections(last_in, last_out);
	return (0);
}

void	execute(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (redirections(cmd, shell) == -1)
		cleanup_child_and_exit(shell, 1);
	if (!cmd->argv || !cmd->argv[0])
		cleanup_child_and_exit(shell, 0);
	if (!cmd->argv[0][0])
	{
		ft_printf(2, "minishell: : command not found\n");
		cleanup_child_and_exit(shell, 127);
	}
	if (is_builtin(cmd->argv))
	{
		execute_builtin(cmd->argv, shell);
		cleanup_child_and_exit(shell, shell->exit_status);
	}
	path = find_correct_path(shell, cmd->argv, cmd->argv[0]);
	try_execute(path, cmd->argv, shell->envp, shell);
}
