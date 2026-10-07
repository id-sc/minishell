/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:21:23 by mutzou            #+#    #+#             */
/*   Updated: 2025/11/05 21:55:46 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Affiche à partir de la dernière occurance*/
char	*ft_strrchr(const char *s, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			ptr = (char *)&s[i];
		}
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (ptr);
}

/*int	main(void)
{
	char	ok[] = "Salade";
	char	c;

	c = 'a';
	printf("%s", ft_strrchr(ok, c));
	return (0);
}*/
