/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:21:13 by mutzou            #+#    #+#             */
/*   Updated: 2025/11/05 21:59:24 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lendest;
	size_t	lensrc;

	j = 0;
	lendest = 0;
	lensrc = ft_strlen(src);
	while (dst[lendest] && lendest < size)
		lendest++;
	if (lendest == size)
		return (size + lensrc);
	i = lendest;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (lendest + lensrc);
}
