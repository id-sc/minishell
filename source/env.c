/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:21:01 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 23:37:51 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_to_env(char **old_env, char *new_var)
{
	int		i;
	char	**new_env;

	if (!new_var || !old_env)
		return (old_env);
	i = 0;
	while (old_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (old_env);
	i = 0;
	while (old_env[i])
	{
		new_env[i] = old_env[i];
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free(old_env);
	return (new_env);
}

void	sort_env(char **copy, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(copy[i], copy[j]) > 0)
			{
				temp = copy[i];
				copy[i] = copy[j];
				copy[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	builtin_env(char **envp, char **args)
{
	int	i;

	i = 0;
	if (ft_strcmp(args[0], "env") == 0)
	{
		if (args[1] != NULL)
		{
			ft_printf(2, "env: '%s': No such file or directory\n", args[1]);
			return (EXIT_FAILURE);
		}
	}
	while (envp[i] && envp)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
