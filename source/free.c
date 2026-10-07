/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:32:47 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 16:07:48 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_env_error(char **env, int i)
{
	while (--i >= 0)
		free(env[i]);
	free(env);
	return (NULL);
}

void	free_redirs_list(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		if (redirs->file)
			free(redirs->file);
		if (redirs->tmp_filename)
			free(redirs->tmp_filename);
		if (redirs->fd > 2)
		{
			close(redirs->fd);
			redirs->fd = -1;
		}
		free(redirs);
		redirs = tmp;
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmds)
		free_cmd_list(shell->cmds);
	if (shell->envp)
		free_tab(shell->envp);
	free(shell);
}

void	free_single_cmd(t_cmd *cmds)
{
	t_redir	*r_tmp;

	if (!cmds)
		return ;
	if (cmds->argv)
	{
		free_tab(cmds->argv);
		cmds->argv = NULL;
	}
	while (cmds->redirs)
	{
		r_tmp = cmds->redirs->next;
		if (cmds->redirs->fd > 2)
			close(cmds->redirs->fd);
		if (cmds->redirs->file)
			free(cmds->redirs->file);
		if (cmds->redirs->tmp_filename)
			free(cmds->redirs->tmp_filename);
		free(cmds->redirs);
		cmds->redirs = r_tmp;
	}
	free(cmds);
}

void	free_cmd_list(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_single_cmd(cmds);
		cmds = tmp;
	}
}
