/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:48:46 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 16:00:20 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimitor(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_redir(char *s)
{
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">")
		|| !ft_strcmp(s, "<<") || !ft_strcmp(s, ">>"));
}

int	get_redir_type(char *s)
{
	if (!ft_strcmp(s, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(s, ">>"))
		return (APPEND);
	if (!ft_strcmp(s, "<"))
		return (REDIR_IN);
	return (REDIR_OUT);
}

t_cmd	*init_cmd(t_cmd **head, t_cmd **current)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_cmd));
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (new);
}

void	add_redir(t_cmd *cmd, char *file, int type)
{
	t_redir	*new;
	t_redir	*last;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->file = ft_strdup(file);
	new->type = type;
	new->fd = -1;
	new->tmp_filename = NULL;
	new->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
