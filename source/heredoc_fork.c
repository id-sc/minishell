/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:50:00 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/24 00:17:03 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	close(g_is_execute);
	g_is_execute = 130;
}

static void	heredoc_child(char *delimiter, t_shell *shell, char *filename)
{
	int	fd;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	handle(shell, delimiter, fd);
	g_is_execute = fd;
	close(fd);
	exit_helper(shell, 1);
	exit(130);
}

int	heredoc(char *delimiter, t_shell *shell, char *filename)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		heredoc_child(delimiter, shell, filename);
	return (heredoc_wait_and_open(pid, filename, shell));
}
