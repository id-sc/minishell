/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:04:07 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/20 18:41:01 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_errors(char *cmd, t_shell *shell, int status)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (shell)
		shell->exit_status = status;
}

// char	*extract_val(char *var_name, t_shell *shell)
// {
// 	char	*env_val;

// 	if (ft_strcmp(var_name, "?") == 0)
// 		return (ft_itoa(shell->exit_status));
// 	env_val = get_env_value(var_name, shell->envp);
// 	if (!env_val)
// 		return (ft_strdup(""));
// 	return (ft_strdup(env_val));
// }
