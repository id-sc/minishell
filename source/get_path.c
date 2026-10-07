/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:15:58 by hesainte          #+#    #+#             */
/*   Updated: 2026/05/23 20:17:50 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_paths(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
			return (shell->envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*check_paths(t_shell *shell, char **cmd, char *name)
{
	char	**paths;
	char	*path;
	char	*all;
	int		i;

	path = get_paths(shell);
	if (!path)
		return (shell->exit_status = 127
			, ft_printf(2, "minishell: %s: command not found\n", name)
			, NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		all = ft_strjoin(path, cmd[0]);
		free(path);
		if (all && access(all, X_OK) == 0)
			return (free_tab(paths), all);
		free(all);
		i++;
	}
	free_tab(paths);
	return (shell->exit_status = 127,
		ft_printf(2, "minishell: %s: command not found\n", name), NULL);
}

char	*find_correct_path(t_shell *shell, char **cmd, char *name)
{
	char	*path;

	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) != 0)
			return (shell->exit_status = 127,
				ft_printf(2,
					"minishell: %s: No such file or directory\n",
					name), NULL);
		else if (access(cmd[0], X_OK) != 0)
			return (shell->exit_status = 126,
				ft_printf(2, "minishell: %s: Permission denied\n",
					name), NULL);
		return (ft_strdup(cmd[0]));
	}
	path = check_paths(shell, cmd, name);
	return (path);
}

void	fill_cmd(t_cmd *curr, char **tokens, int *i)
{
	if (tokens[*i] && is_redir(tokens[*i]))
	{
		add_redir(curr, tokens[*i + 1], get_redir_type(tokens[*i]));
		*i += 2;
	}
	else if (tokens[*i])
	{
		curr->argv = add_to_argv(curr->argv, tokens[(*i)++]);
	}
}

t_cmd	*parse_tokens(char **tokens, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*curr;
	int		i;

	i = 0;
	(void)shell;
	head = NULL;
	curr = NULL;
	while (tokens[i])
	{
		if (!curr || !ft_strcmp(tokens[i], "|"))
		{
			init_cmd(&head, &curr);
			if (!ft_strcmp(tokens[i], "|"))
				i++;
		}
		while (tokens[i] && ft_strcmp(tokens[i], "|"))
			fill_cmd(curr, tokens, &i);
	}
	return (head);
}
