/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:55:02 by hesainte          #+#    #+#             */
/*   Updated: 2026/05/23 15:21:06 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

void	init_shell_env(t_shell *shell)
{
	update_pwd(shell);
	update_shlvl(shell);
}

void	process(t_shell *shell)
{
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->cmds && !shell->cmds->next && is_builtin(shell->cmds->argv))
	{
		if (redirections(shell->cmds, shell) != -1)
			shell->exit_status = execute_builtin(shell->cmds->argv, shell);
		else
			shell->exit_status = 1;
	}
	else
		execute_pipeline(shell);
	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
	if (shell->stdin_backup >= 0)
	{
		close(shell->stdin_backup);
		shell->stdin_backup = -1;
	}
	if (shell->stdout_backup >= 0)
	{
		close(shell->stdout_backup);
		shell->stdout_backup = -1;
	}
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = copy_env(envp);
	shell->cmds = NULL;
	shell->exit_status = 0;
	shell->exit_requested = 0;
	shell->stdin_backup = -1;
	shell->stdout_backup = -1;
	init_shell_env(shell);
}

void	init_signals(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGFPE, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	*shell;
	int		status;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	init_shell(shell, envp);
	init_signals();
	while (loop(shell))
		;
	if (!shell->exit_requested)
		ft_putstr_fd("exit\n", 2);
	status = shell->exit_status;
	exit_helper(shell, 1);
	return (status);
}
