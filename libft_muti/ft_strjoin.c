/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:34:38 by mutzou            #+#    #+#             */
/*   Updated: 2026/04/16 18:04:53 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	new_s = malloc(sizeof(char) * len + 1);
	if (!new_s)
		return (NULL);
	while (s1[++i])
		new_s[j++] = s1[i];
	i = -1;
	while (s2[++i])
		new_s[j++] = s2[i];
	new_s[j] = '\0';
	return (new_s);
}
