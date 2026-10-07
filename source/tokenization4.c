/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:59:21 by hesainte          #+#    #+#             */
/*   Updated: 2026/05/23 16:05:33 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_lenght(const char *line, int i)
{
	t_QuoteState	state;
	char			c;

	state = NONE;
	while (line[i])
	{
		c = line[i];
		if (state == NONE)
		{
			if (c == '\'')
				state = SINGLE_QUOTE;
			else if (c == '"')
				state = DOUBLE_QUOTE;
			else if (c == ' ' || is_delimitor(c))
				break ;
		}
		else if (state == SINGLE_QUOTE && c == '\'')
			state = NONE;
		else if (state == DOUBLE_QUOTE && (c == '"'))
			state = NONE;
		i++;
	}
	return (i);
}

int	token_length(const char *line, int start)
{
	int	end;

	if (line[start] && is_delimitor(line[start]))
	{
		if (line[start + 1] && line[start + 1] == line[start]
			&& (line[start] == '<' || line[start] == '>'))
			return (2);
		return (1);
	}
	end = process_lenght(line, start);
	return (end - start);
}
