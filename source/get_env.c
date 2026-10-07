/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:57:35 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/20 18:40:30 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((i < n && s1[i]) || s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

char	*get_env_value(char *var_name, char **env)
{
	int	i;
	int	len;

	i = 0;
	if (!env || !var_name)
		return ("");
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			return (env[i] + len + 1);
		}
		i++;
	}
	return ("");
}

char	*extract_val(char *var_name, t_shell *shell)
{
	char	*env_val;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_status));
	env_val = get_env_value(var_name, shell->envp);
	if (!env_val)
		return (ft_strdup(""));
	return (ft_strdup(env_val));
}

// void increment_shlvl(char **env)
// {
// 	int		i;
// 	int		shlvl;
// 	char	*new_var;
// 	char	*value;

// 	i = 0;
// 	value = get_env_value("SHLVL", env);
// 	shlvl = ft_atoi(value);
// 	shlvl++;

// 	new_var = ft_strjoin("SHLVL=", ft_itoa(shlvl));

// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
// 		{
// 			free(env[i]);
// 			env[i] = new_var;
// 			return;
// 		}
// 		i++;
// 	}
// }

/*int	main(int argc, char **argv, char **envp)
{
	printf("USER: %s\n", get_env_value("USER", envp));
	printf("HOME: %s\n", get_env_value("HOME", envp));

    return (0);
}*/
