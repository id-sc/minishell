/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 08:00:02 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/25 16:44:54 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC && redir->fd > 2)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			if (redir->type == HEREDOC && redir->tmp_filename)
				unlink(redir->tmp_filename);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

char	*get_unique_filename(int index)
{
	char	*idx_str;
	char	*filename;

	idx_str = ft_itoa(index);
	filename = ft_strjoin(".heredoc_", idx_str);
	free(idx_str);
	return (filename);
}

int	heredoc_wait_and_open(pid_t pid, char *filename, t_shell *shell)
{
	int	status;
	int	read_fd;

	waitpid(pid, &status, 0);
	if ((WEXITSTATUS(status) == 130))
	{
		shell->exit_status = 130;
		unlink(filename);
		printf("\n");
		return (-1);
	}
	read_fd = open(filename, O_RDONLY);
	if (read_fd < 0)
		return (-1);
	return (read_fd);
}
