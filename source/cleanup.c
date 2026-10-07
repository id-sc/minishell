/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:55:02 by hesainte          #+#    #+#             */
/*   Updated: 2026/05/24 00:19:24 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **t)
{
	int	i;

	if (!t)
		return ;
	i = 0;
	while (t[i])
	{
		free(t[i]);
		t[i] = NULL;
		i++;
	}
	free(t);
	t = NULL;
}

void	exit_helper(t_shell *shell, bool fd)
{
	if (!shell)
		return ;
	rl_clear_history();
	if (shell->stdin_backup > 2)
		close(shell->stdin_backup);
	if (shell->stdout_backup > 2)
		close(shell->stdout_backup);
	if (fd)
	{
		close(0);
		close(1);
	}
	if (shell->cmds)
	{
		free_cmd_list(shell->cmds);
		shell->cmds = NULL;
	}
	if (shell->envp)
		free_tab(shell->envp);
	free(shell);
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
