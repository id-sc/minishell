/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:32:03 by mutzou            #+#    #+#             */
/*   Updated: 2025/11/12 10:21:17 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunbr(unsigned int nbr, int *count)
{
	if (nbr >= 10)
		ft_putunbr(nbr / 10, count);
	ft_putchar_fd(nbr % 10 + '0', 1, count);
}
