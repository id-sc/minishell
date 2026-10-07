/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:19:56 by mutzou            #+#    #+#             */
/*   Updated: 2025/11/05 14:33:17 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/*int main()
{
        int letter1 = 'a';
        int letter2 = 'b';
        printf("%c", ft_toupper(letter1));
        printf("%c", ft_toupper(letter2));
        return (0);
}*/
