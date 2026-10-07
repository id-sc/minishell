/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:23:38 by heidi             #+#    #+#             */
/*   Updated: 2026/05/08 21:43:30 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd[])
{
	const char	*builtins[9];
	int			i;

	if (!cmd || !cmd[0])
		return (0);
	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], cmd[0]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(char *cmd[], t_shell *shell)
{
	int	ret;

	if (ft_strcmp("exit", cmd[0]) == 0)
		ret = builtin_exit(cmd, shell);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
		ret = builtin_pwd();
	else if (ft_strcmp("echo", cmd[0]) == 0)
		ret = builtin_echo(cmd);
	else if (ft_strcmp("cd", cmd[0]) == 0)
		ret = builtin_cd(cmd, shell);
	else if (ft_strcmp("env", cmd[0]) == 0)
		ret = builtin_env(shell->envp, cmd);
	else if (ft_strcmp("export", cmd[0]) == 0)
		ret = do_export(shell, cmd);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		ret = builtin_unset(shell, cmd);
	else
		return (127);
	return (ret);
}
