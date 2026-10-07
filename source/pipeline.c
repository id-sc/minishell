/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:55:02 by hesainte          #+#    #+#             */
/*   Updated: 2026/05/23 20:04:39 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (cmd->argv && cmd->argv[0])
// 		{
// 			if (is_builtin(cmd->argv))
// 				execute_builtin(cmd->argv, shell->envp);
// 			else
// 				execute_cmd(cmd->argv, shell);
// 		}

int	builtin_modifies_shell(char **cmd)
{
	return (ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "unset") == 0
		|| ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "exit") == 0);
}

void	update_exit(t_shell *shell, int status)
{
	if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
	}
	else if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

void	child_process(t_shell *shell, t_cmd *cmd, int p[2], int fd_in)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->next)
	{
		if (p[0] != -1)
			close(p[0]);
		if (p[1] != -1)
		{
			dup2(p[1], STDOUT_FILENO);
			close(p[1]);
		}
	}
	execute(cmd, shell);
	close(0);
	close(1);
	exit(shell->exit_status);
}

int	execute_command(t_shell *shell, t_cmd *cmd, int *fd_in, int p[2])
{
	pid_t	pid;

	if (cmd->next && pipe(p) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_process(shell, cmd, p, *fd_in);
	if (*fd_in != -1)
	{
		close(*fd_in);
	}
	if (cmd->next)
	{
		close(p[1]);
		*fd_in = p[0];
	}
	else
		*fd_in = -1;
	return (pid);
}

/*void	execute_pipeline(t_shell *shell)
{
	t_cmd	*cmd;
	int		p[2];
	int		fd_in;
	int		st;
	pid_t	pid;

	fd_in = STDIN_FILENO;
	cmd = shell->cmds;
	while (cmd)
	{
		pid = execute_command(shell, cmd, &fd_in, p);
		if (pid == -1)
			return ;
		cmd = cmd->next;
	}
	fd_in = wait(&st);
	while (fd_in > 0)
	{
		if (fd_in == pid)
			update_exit(shell, st);
		fd_in = wait(&st);
	}
}*/

void	execute_pipeline(t_shell *shell)
{
	t_cmd	*cmd;
	int		p[2];
	int		fd_in;
	int		st;
	pid_t	pid;

	fd_in = -1;
	p[0] = -1;
	p[1] = -1;
	cmd = shell->cmds;
	while (cmd)
	{
		pid = execute_command(shell, cmd, &fd_in, p);
		cmd = cmd->next;
	}
	if (fd_in > 0)
		close(fd_in);
	if (waitpid(pid, &st, 0) != -1)
		update_exit(shell, st);
	while (wait(NULL) > 0)
		;
}
