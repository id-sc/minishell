/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:15:39 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 15:41:10 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp)
{
	char	**new_env;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_env[j] = ft_strdup(envp[j]);
		if (!new_env[j])
			return (free_env_error(new_env, j));
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	match_env_key(const char *env, const char *key)
{
	int	len;

	len = ft_strlen(key);
	if (ft_strncmp(env, key, len) == 0 && env[len] == '=')
		return (1);
	return (0);
}

void	replace_env_var(t_shell *shell, const char *key, const char *value)
{
	int		i;
	char	*tmp;
	char	*new_var;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	if (!new_var)
		return ;
	i = 0;
	while (shell->envp[i])
	{
		if (match_env_key(shell->envp[i], key))
		{
			free(shell->envp[i]);
			shell->envp[i] = new_var;
			return ;
		}
		i++;
	}
	shell->envp = add_to_env(shell->envp, new_var);
	free(new_var);
}

void	update_shlvl(t_shell *shell)
{
	char	*value;
	char	*next_value;
	int		shlvl;

	value = get_env_value("SHLVL", shell->envp);
	if (!value || !*value)
		shlvl = 1;
	else
		shlvl = ft_atoi(value) + 1;
	next_value = ft_itoa(shlvl);
	if (!next_value)
		return ;
	replace_env_var(shell, "SHLVL", next_value);
	free(next_value);
}
