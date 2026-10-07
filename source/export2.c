/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:33:15 by hesainte          #+#    #+#             */
/*   Updated: 2026/05/23 15:54:10 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_name(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_var(char **env, char *var_to_find)
{
	int	i;
	int	len;

	if (!env || !var_to_find)
		return (-1);
	len = 0;
	while (var_to_find[len] && var_to_find[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_to_find, len) == 0)
		{
			if (env[i][len] == '=' || env[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}
