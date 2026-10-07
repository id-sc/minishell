/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 10:52:48 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 15:03:27 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_error(char *msg, t_shell *shell)
{
	ft_putstr_fd("minishell: syntax error near ", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (shell)
		shell->exit_status = 2;
	return (-1);
}

int	process_error(char **tokens, t_shell *shell, int i)
{
	if (ft_strcmp(tokens[i], "||") == 0)
		return (put_error("token '||'\n", shell));
	if (ft_strcmp(tokens[i], "|") == 0)
	{
		if (i == 0 || !tokens[i + 1])
			return (put_error("unexpected token '|'\n", shell));
		if (ft_strcmp(tokens[i + 1], "|") == 0)
			return (put_error("token '||'\n", shell));
		return (0);
	}
	if (is_redir(tokens[i]))
	{
		if (!tokens[i + 1])
			return (put_error("token 'newline'\n", shell));
		if (ft_strcmp(tokens[i + 1], "|") == 0)
			return (put_error("unexpected token '|'\n", shell));
		if (is_redir(tokens[i + 1]))
			return (put_error("unexpected token\n", shell));
	}
	return (0);
}

// int	process_error(char **tokens, t_shell *shell, int i)
// {
// 	print_cmds(shell->cmds);
// 	printf("tiai\n");
// 	if (ft_strcmp(tokens[i], "||") == 0
// 		|| (ft_strcmp(tokens[i], "|") == 0
// 			&& tokens[i + 1] && ft_strcmp(tokens[i + 1], "|") == 0))
// 		return (put_error("token '||'\n", shell));
// 	if (ft_strcmp(tokens[i], "|") == 0)
// 	{
// 		if (i == 0 || !tokens[i + 1])
// 			return (put_error("unexpected toooken '|'\n", shell), -1);
// 		return (0);
// 	}
// 	else if (ft_strcmp(tokens[i], "<") == 0
// 		|| ft_strcmp(tokens[i], ">") == 0
// 		|| ft_strcmp(tokens[i], "<<") == 0
// 		|| ft_strcmp(tokens[i], ">>") == 0)
// 	{
// 		if (!tokens[i + 1])
// 			return (put_error("token 'newline'\n", shell));
// 		if (ft_strcmp(tokens[i + 1], "|") == 0)
// 			put_error("token '|'\n", shell);
// 		if (ft_strcmp(tokens[i + 1], "<") == 0
// 			|| ft_strcmp(tokens[i + 1], ">") == 0)
// 			return (put_error("unexpected token\n", shell), -1);
// 	}
// 	return (0);
// }

int	pipe_count(char **tokens, t_shell *shell)
{
	int	i;
	int	nb;
	int	res;

	nb = 0;
	i = 0;
	if (!tokens || !tokens[0])
		return (0);
	while (tokens[i])
	{
		res = process_error(tokens, shell, i);
		if (res == -1)
			return (-1);
		nb += res;
		i++;
	}
	return (nb);
}
