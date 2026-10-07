/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:07:38 by mutzou            #+#    #+#             */
/*   Updated: 2025/11/12 10:20:58 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_fd(int nbr, int fd, int *count)
{
	size_t	nb;

	nb = nbr;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd, count);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd, count);
	ft_putchar_fd(nb % 10 + '0', fd, count);
}
