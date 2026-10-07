/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 21:24:00 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 15:34:48 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char *rl, t_shell *shell)
{
	char	**tokens;
	int		p_count;
	int		backup;

	tokens = tokenize(rl, shell);
	if (!tokens)
		return (0);
	p_count = pipe_count(tokens, shell);
	if (p_count == -1)
	{
		backup = shell->exit_status;
		free_tab(tokens);
		shell->exit_status = backup;
		return (0);
	}
	shell->cmds = parse_tokens(tokens, shell);
	free_tab(tokens);
	expansion_cmds(shell);
	cmds_quotes(shell->cmds);
	return (1);
}

void	flag_process(t_shell *shell)
{
	g_is_execute = 2;
	if (shell->cmds && (shell->cmds->argv || shell->cmds->redirs))
		process(shell);
	g_is_execute = 0;
}

void	process_input(char *rl, t_shell *shell)
{
	if (parse(rl, shell))
	{
		if (prepare_heredocs(shell) != -1)
			flag_process(shell);
	}
	free(rl);
	if (shell->cmds)
	{
		close_heredocs(shell->cmds);
		free_cmd_list(shell->cmds);
		shell->cmds = NULL;
	}
}

int	loop(t_shell *shell)
{
	char	*rl;
	int		i;

	rl = readline("minishell> ");
	if (!rl)
		return (0);
	if (g_is_execute)
	{
		shell->exit_status = 130;
		g_is_execute = 0;
	}
	i = 0;
	while (rl[i] && (rl[i] == ' ' || rl[i] == '\t'))
		i++;
	if (rl[i])
		add_history(rl);
	process_input(rl, shell);
	return (!shell->exit_requested);
}

void	process_argv_quotes(t_cmd *cmd)
{
	int		k;
	char	*old;

	k = 0;
	while (cmd->argv && cmd->argv[k])
	{
		old = cmd->argv[k];
		cmd->argv[k] = clear_quotes(old);
		free(old);
		k++;
	}
}
