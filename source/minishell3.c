/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:12 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 15:40:56 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redir_quotes(t_cmd *cmd)
{
	t_redir	*redir;
	char	*old;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->file)
		{
			old = redir->file;
			redir->file = clear_quotes(old);
			free(old);
		}
		redir = redir->next;
	}
}

void	cmds_quotes(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		process_argv_quotes(tmp);
		process_redir_quotes(tmp);
		tmp = tmp->next;
	}
}

void	update_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	replace_env_var(shell, "PWD", cwd);
	free(cwd);
}
