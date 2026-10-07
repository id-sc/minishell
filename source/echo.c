/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:13:02 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/12 12:01:22 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag(char *s)
{
	int	j;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	j = 1;
	while (s[j] == 'n')
		j++;
	return (s[j] == '\0');
}

int	check_n(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i] && is_flag(cmd[i]))
	{
		i++;
	}
	return (i);
}

int	builtin_echo(char **cmd)
{
	int	i;
	int	n;

	i = check_n(cmd);
	if (i > 1)
		n = 1;
	else
		n = 0;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

// int	builtin_echo(char **cmd)
// {
// 	int	i;
// 	int	j;
// 	int	n_line;

// 	i = 1;
// 	n_line = 1;
// 	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
// 	{
// 		j = 1;
// 		while (cmd[i][j] == 'n')
// 			j++;
// 		if (cmd[i][j] == '\0')
// 		{
// 			n_line = 0;
// 			i++;
// 		}
// 		else
// 			break ;
// 	}
// 	while (cmd[i])
// 	{
// 		ft_putstr_fd(cmd[i], 1);
// 		if (cmd[i + 1])
// 			ft_putstr_fd(" ", 1);
// 		i++;
// 	}
// 	if (n_line)
// 		ft_putstr_fd("\n", 1);
// 	return (EXIT_SUCCESS);
// }
