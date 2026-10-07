/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:55:02 by hesainte          #+#    #+#             */
/*   Updated: 2026/05/15 15:39:03 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	fork_and_execute_cmd(t_shell *shell)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		execute(shell->cmds, shell);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		update_exit(shell, status);
// 	}
// }
