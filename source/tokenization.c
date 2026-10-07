/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:55:02 by hesainte          #+#    #+#             */
/*   Updated: 2026/05/23 19:03:10 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_QuoteState	process_token(char *line, int *i)
{
	t_QuoteState	state;

	state = NONE;
	while (line[*i])
	{
		if (state == NONE)
		{
			if (line[*i] == '\'')
				state = SINGLE_QUOTE;
			else if (line[*i] == '"')
				state = DOUBLE_QUOTE;
			else if (line[*i] == ' ' || is_delimitor(line[*i]))
				break ;
		}
		else if (state == SINGLE_QUOTE && line[*i] == '\'')
			state = NONE;
		else if (state == DOUBLE_QUOTE && line[*i] == '"')
			state = NONE;
		(*i)++;
	}
	return (state);
}

int	handle_delimiter(char *line, int *i)
{
	if ((line[*i + 1] && line[*i + 1] == line[*i])
		&& (line[*i] == '<' || line[*i] == '>'))
		*i += 2;
	else
		(*i)++;
	return (1);
}

static int	handle_word(char *line, int *i, t_shell *shell)
{
	t_QuoteState	state;

	state = process_token(line, i);
	if (state != NONE)
	{
		write(2, "minishell: unclosed quotes\n", 27);
		shell->exit_status = 2;
		return (-1);
	}
	return (1);
}

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	count_token(char *line, t_shell *shell)
{
	int	i;
	int	tokens;

	i = 0;
	tokens = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		tokens++;
		if (is_delimitor(line[i]))
			handle_delimiter(line, &i);
		else if (handle_word(line, &i, shell) == -1)
			return (-1);
	}
	return (tokens);
}
