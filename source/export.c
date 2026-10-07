/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:32:34 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 20:17:12 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_env(char **env, int count)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			return (free(copy), NULL);
		}
	}
	copy[count] = NULL;
	return (copy);
}

void	builtin_export(char **env)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	while (env[count])
		count++;
	copy = dup_env(env, count);
	if (!copy)
		return ;
	sort_env(copy, count);
	i = 0;
	while (i < count)
		printf("declare -x %s\n", copy[i++]);
	free(copy);
}

char	**modify_env(char **env, char *new)
{
	int		index;
	char	**new_env;

	if (!new)
		return (env);
	index = find_var(env, new);
	if (index != -1)
	{
		free(env[index]);
		env[index] = ft_strdup(new);
		return (env);
	}
	else
	{
		new_env = add_to_env(env, new);
		return (new_env);
	}
}

int	do_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
	{
		builtin_export(shell->envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (is_valid_env_name(args[i]))
			shell->envp = modify_env(shell->envp, args[i]);
		else
		{
			ft_printf(2,
				"minishell: export: `%s': not a valid identifier\n", args[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
