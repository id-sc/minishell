/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:14:18 by marvin            #+#    #+#             */
/*   Updated: 2025/11/10 16:14:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	handle_conversion(const char *ptr, int i, int *count, va_list ap)
{
	uintptr_t	p;

	if (ptr[i] == 's')
		ft_putstr_fd(va_arg(ap, char *), 1, count);
	else if (ptr[i] == 'd' || ptr[i] == 'i')
		ft_putnbr_fd(va_arg(ap, int), 1, count);
	else if (ptr[i] == 'c')
		ft_putchar_fd(va_arg(ap, int), 1, count);
	else if (ptr[i] == 'p')
	{
		p = va_arg(ap, uintptr_t);
		if (p == 0)
			return (ft_putstr_fd("(nil)", 1, count));
		ft_putstr_fd("0x", 1, count);
		ft_putnbrhexa(p, 0, count);
	}
	else if (ptr[i] == 'x')
		ft_putnbrhexa(va_arg(ap, unsigned int), 0, count);
	else if (ptr[i] == 'X')
		ft_putnbrhexa(va_arg(ap, unsigned int), 1, count);
	else if (ptr[i] == '%')
		ft_putchar_fd('%', 1, count);
	else if (ptr[i] == 'u')
		ft_putunbr(va_arg(ap, unsigned int), count);
}

int	ft_printf(int fd, const char *ptr, ...)
{
	va_list	ap;
	size_t	i;
	int		count;

	count = 0;
	i = -1;
	if (ptr == NULL)
		return (-1);
	va_start(ap, ptr);
	while (ptr[++i])
	{
		if (ptr[i] == '%')
		{
			i++;
			handle_conversion(ptr, i, &count, ap);
		}
		else
		{
			write(fd, &ptr[i], 1);
			count++;
		}
	}
	return (count);
}

// int	main(void)
// {
// 	int	i = 0;
// 	int j = 0;
// 	i = ft_printf("fds %pdas\n", (void *)0);
// 	j = printf("fds %pdas\n", (void *)0);
// 	printf("%d = j et %d = i\n", j, i);
// }
