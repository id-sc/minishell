/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:17:34 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/22 17:57:40 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **cmd, t_shell *shell)
{
	int	status;

	if (!cmd[1])
	{
		shell->exit_requested = 1;
		return (shell->exit_status);
	}
	if (!is_str_digit(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		shell->exit_status = 2;
		shell->exit_requested = 1;
		return (2);
	}
	if (cmd[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	status = atoi(cmd[1]);
	shell->exit_status = status % 256;
	exit_shell(shell, shell->exit_status);
	return (shell->exit_status);
}

void	exit_shell(t_shell *shell, int status)
{
	exit_helper(shell, 1);
	exit(status);
}
