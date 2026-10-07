/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutzou <mutzou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:52:51 by mutzou            #+#    #+#             */
/*   Updated: 2026/03/02 15:56:43 by mutzou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

size_t	count_words(char const *str, char c)
{
	size_t	i;
	size_t	nb_words;

	i = 0;
	nb_words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			nb_words++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (nb_words);
}

char	*put_word(char const *s, size_t *i, char c)
{
	char	*ret;
	size_t	len;
	size_t	k;

	len = 0;
	k = 0;
	while (s[*i + len] && s[*i + len] != c)
		len++;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (s[*i] && s[*i] != c)
	{
		ret[k] = s[*i];
		(*i)++;
		k++;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	result[count_words(s, c)] = NULL;
	while (j < count_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			result[j] = put_word(s, &i, c);
			if (!result[j])
				return (ft_free(result), NULL);
			j++;
		}
	}
	return (result);
}
