/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:36:13 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 19:15:41 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clear_quotes(char *str)
{
	int				i;
	int				j;
	char			*new;
	t_QuoteState	state;

	i = -1;
	j = 0;
	state = NONE;
	new = malloc(ft_strlen(str) + 1);
	if (!str || !(new))
		return (NULL);
	while (str[++i])
	{
		if (state == NONE && (str[i] == '\'' || str[i] == '\"'))
			state = (str[i] == '\"') + 1;
		else if ((state == SINGLE_QUOTE && str[i] == '\'')
			|| (state == DOUBLE_QUOTE && str[i] == '\"'))
			state = NONE;
		else
			new[j++] = str[i];
	}
	new[j] = '\0';
	return (new);
}

void	process_tokenize(char *line, char **token, int nb)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (line[i] && j < nb)
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		len = token_length(line, i);
		token[j++] = ft_substr(line, i, len);
		i += len;
	}
}

char	**tokenize(char *line, t_shell *shell)
{
	int		nb;
	char	**token;

	if (!line)
		return (NULL);
	nb = count_token(line, shell);
	if (nb <= 0)
		return (NULL);
	token = malloc(sizeof(char *) * (nb + 1));
	if (!token)
		return (NULL);
	process_tokenize(line, token, nb);
	token[nb] = NULL;
	return (token);
}

char	**add_to_argv(char **argv, char *token)
{
	int		count;
	char	**new_argv;
	int		i;

	count = 0;
	while (argv && argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[count] = ft_strdup(token);
	if (!new_argv[count])
	{
		free(new_argv);
		return (NULL);
	}
	new_argv[count + 1] = NULL;
	free(argv);
	return (new_argv);
}
