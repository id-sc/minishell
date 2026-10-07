/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:30:12 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 23:38:50 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(char *line, t_shell *shell, int fd, int should_expand)
{
	char	*expand;

	if (should_expand)
		expand = expand_variable(line, shell);
	else
		expand = line;
	if (expand)
	{
		write(fd, expand, ft_strlen(expand));
		write(fd, "\n", 1);
	}
	free(expand);
}

void	handle(t_shell *shell, char *delimiter, int fd)
{
	char	*line;
	int		should_expand;
	char	*clean_delim;

	should_expand = !is_quoted(delimiter);
	clean_delim = remove_quotes(delimiter);
	while (1)
	{
		line = readline(">");
		if (!line || (ft_strcmp(line, clean_delim) == 0))
		{
			free(line);
			free(clean_delim);
			if (fd >= 2)
				close(fd);
			exit_helper(shell, 0);
			if (g_is_execute == 130)
				exit(130);
			exit(0);
		}
		process_line(line, shell, fd, should_expand);
	}
	free(clean_delim);
}

int	prepare_heredocs(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		index;

	index = 0;
	cmd = shell->cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				redir->tmp_filename = get_unique_filename(index++);
				redir->fd = heredoc
					(redir->file, shell, redir->tmp_filename);
				if (redir->fd == -1)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
