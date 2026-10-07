/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:08:45 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 14:17:32 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || (c == '_'));
}

void	update_quote_state(char c, t_QuoteState *state)
{
	if (c == '\'' && *state == NONE)
		*state = SINGLE_QUOTE;
	else if (c == '\"' && *state == NONE)
		*state = DOUBLE_QUOTE;
	else if ((c == '\'' && *state == SINGLE_QUOTE)
		|| (c == '\"' && *state == DOUBLE_QUOTE))
		*state = NONE;
}

char	*new_value(char *str, int dollar_pos, t_shell *shell)
{
	char	*res;
	char	*tmp[3];
	int		i;

	i = dollar_pos + 1;
	if (str[i] == '?')
		i++;
	else
		while (str[i] && is_valid(str[i]))
			i++;
	tmp[0] = ft_substr(str, dollar_pos + 1, i - (dollar_pos + 1));
	tmp[1] = extract_val(tmp[0], shell);
	if (!tmp[1])
		tmp[1] = ft_strdup("");
	res = ft_substr(str, 0, dollar_pos);
	if (!res)
		return (free(tmp[0]), free(tmp[1]), free(str), NULL);
	tmp[2] = ft_strjoin(res, tmp[1]);
	free(res);
	if (!tmp[0] || !tmp[1] ||!tmp[2])
		return (free(tmp[0]), free(tmp[1]), free(tmp[2]), free(str), NULL);
	res = ft_strjoin(tmp[2], &str[i]);
	return (free(tmp[0]), free(tmp[1]), free(tmp[2]), free(str), res);
}

char	*expand_variable(char *str, t_shell *shell)
{
	int				i;
	t_QuoteState	state;

	i = 0;
	state = NONE;
	if (!str)
		return (NULL);
	while (str[i])
	{
		update_quote_state(str[i], &state);
		if (str[i] == '$' && state != SINGLE_QUOTE)
		{
			if (str[i + 1] && (is_valid(str[i + 1]) || str[i + 1] == '?'))
			{
				str = new_value(str, i, shell);
				if (!str)
					return (NULL);
				i--;
			}
		}
		i++;
	}
	return (str);
}

void	expansion_cmds(t_shell *shell)
{
	t_cmd	*current_cmd;
	t_redir	*redir;
	int		i;

	current_cmd = shell->cmds;
	while (current_cmd)
	{
		i = 0;
		while (current_cmd->argv && current_cmd->argv[i])
		{
			current_cmd->argv[i] = expand_variable(current_cmd->argv[i], shell);
			i++;
		}
		redir = current_cmd->redirs;
		while (redir)
		{
			if (redir->type != HEREDOC && redir->file)
				redir->file = expand_variable(redir->file, shell);
			redir = redir->next;
		}
		current_cmd = current_cmd->next;
	}
}
