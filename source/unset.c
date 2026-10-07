/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:24:51 by mutzou            #+#    #+#             */
/*   Updated: 2026/04/15 18:46:53 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_process(char **envp, char *var)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0
			&& (envp[i][len] == '\0' || envp[i][len] == '='))
		{
			free(envp[i]);
			j = i;
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			continue ;
		}
		i++;
	}
}

int	builtin_unset(t_shell *shell, char **args)
{
	int	k;

	if (!shell->envp || !args || !args[1])
		return (0);
	k = 1;
	while (args[k])
	{
		unset_process(shell->envp, args[k]);
		k++;
	}
	return (0);
}
