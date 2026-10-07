/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:25:29 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 20:54:13 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_var(t_shell *shell, char *key, char *value)
{
	int		i;
	char	*new_line;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(key, "=");
	new_line = ft_strjoin(tmp, value);
	free(tmp);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, ft_strlen(key)) == 0
			&& shell->envp[i][ft_strlen(key)] == '=')
		{
			free(shell->envp[i]);
			shell->envp[i] = new_line;
			return ;
		}
		i++;
	}
	free(new_line);
}

static char	*get_cd_target(char **cmd, char **env)
{
	char	*target;

	if (!cmd[1])
	{
		target = get_env_value("HOME", env);
		if (!target || *target == '\0')
			return (ft_printf(2, "minishell: cd: HOME not set\n"), NULL);
		return (target);
	}
	if (strcmp(cmd[1], "-") == 0)
	{
		target = get_env_value("OLDPWD", env);
		if (!target || *target == '\0')
			return (ft_printf(2
					, "minishell: cd: OLDPWD not set\n"), NULL);
		printf("%s\n", target);
		return (target);
	}
	return (cmd[1]);
}

// int	builtin_cd(char **cmd, t_shell *shell)
// {
// 	char	old[1024];
// 	char	*target;

// 	if (cmd[1] && cmd[2])
// 	{
// 		fprintf(stderr, "minishell: cd: too many arguments\n");
// 		shell->exit_status = 1;
// 		return (1);
// 	}
// 	if (!getcwd(old, sizeof(old)))
// 		return (perror("getcwd"), EXIT_FAILURE);
// 	target = get_cd_target(cmd, shell->envp);
// 	if (!target)
// 	{
// 		shell->exit_status = 1;
// 		return (EXIT_FAILURE);
// 	}
// 	if (chdir(target) != 0)
// 	{
// 		fprintf(stderr, "minishell: cd: %s: No such file or directory\n",
// 			target);
// 		shell->exit_status = 1;
// 		return (EXIT_FAILURE);
// 	}
// 	update_env_var(shell, "OLDPWD", old);
// 	update_pwd(shell);
// 	shell->exit_status = 0;
// 	return (EXIT_SUCCESS);
// }

static int	cd_error(t_shell *shell, char *msg, char *arg)
{
	if (arg)
		ft_printf(2, "minishell: cd: %s: %s\n", arg, msg);
	else
		ft_printf(2, "minishell: cd: %s\n", msg);
	shell->exit_status = 1;
	return (EXIT_FAILURE);
}

static int	change_directory(char *target, char *old, t_shell *shell)
{
	if (chdir(target) != 0)
		return (cd_error(shell, "No such file or directory", target));
	if (old[0])
		update_env_var(shell, "OLDPWD", old);
	update_pwd(shell);
	shell->exit_status = 0;
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **cmd, t_shell *shell)
{
	char	old[1024];
	char	*target;

	if (cmd[1] && cmd[2])
		return (cd_error(shell, "too many arguments", NULL));
	if (!getcwd(old, sizeof(old)))
	{
		perror("getcwd");
		old[0] = '\0';
	}
	target = get_cd_target(cmd, shell->envp);
	if (!target)
		return (shell->exit_status = 1, EXIT_FAILURE);
	return (change_directory(target, old, shell));
}
