/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:52:00 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/25 16:42:30 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_child(t_shell *shell)
{
	if (shell->stdin_backup != -1)
		close(shell->stdin_backup);
	if (shell->stdout_backup != -1)
		close(shell->stdout_backup);
	if (shell->cmds)
		free_cmd_list(shell->cmds);
	if (shell->envp)
		free_tab(shell->envp);
	free(shell);
}

void	cleanup_child_and_exit(t_shell *shell, int status)
{
	if (status != -1)
		shell->exit_status = status;
	cleanup_child(shell);
	close(0);
	close(1);
	exit(status);
}

void	try_execute(char *path, char **argv, char **envp, t_shell *shell)
{
	if (!path)
		cleanup_child_and_exit(shell, shell->exit_status);
	if (execve(path, argv, envp) == -1)
	{
		perror("minishell: execve");
		free(path);
		cleanup_child_and_exit(shell, 126);
	}
}
