/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:59:03 by mutzou            #+#    #+#             */
/*   Updated: 2025/11/08 21:11:32 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*copy;

	copy = lst;
	i = 0;
	while (copy != NULL)
	{
		i++;
		copy = copy->next;
	}
	return (i);
}
