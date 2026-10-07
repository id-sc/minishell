/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesainte <hesainte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:57:33 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 14:11:23 by hesainte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_is_execute = 0;

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		if (g_is_execute == 2)
			write(1, "\n", 1);
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_is_execute = 1;
		}
	}
}
