/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:37:51 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 20:40:56 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrhexa(uintptr_t nbr, bool maj, int *count)
{
	const char	nb[] = "0123456789abcdef";
	const char	nb2[] = "0123456789ABCDEF";

	if (nbr >= 16)
		ft_putnbrhexa(nbr / 16, maj, count);
	if (maj)
		ft_putchar_fd(nb2[nbr % 16], 1, count);
	else
		ft_putchar_fd(nb[nbr % 16], 1, count);
}
