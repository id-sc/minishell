/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:05:35 by mutzou            #+#    #+#             */
/*   Updated: 2026/05/23 20:05:35 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

int		ft_printf(int fd, const char *ptr, ...);
void	ft_putchar_fd(char c, int fd, int *count);
void	ft_putstr_fd(char *s, int fd, int *count);
void	ft_putnbr_fd(int nbr, int fd, int *count);
void	ft_putnbrhexa(uintptr_t nbr, bool maj, int *count);
void	ft_putunbr(unsigned int nbr, int *count);

#endif
