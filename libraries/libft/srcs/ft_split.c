/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:02:58 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/28 13:21:07 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_arr_size(const char *s, char c)
{
	size_t	l;

	l = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			l++;
		while (*s && *s != c)
			s++;
	}
	return (l);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	char	**arr;
	char	*i;

	if (!s || !(arr = (char **)ft_calloc(ft_arr_size(s, c) + 1, \
					sizeof(char *))))
		return (0);
	ret = arr;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		i = (ft_strchr(s, c) ? ft_strchr(s, c) : ft_strchr(s, '\0'));
		if (*s)
			*arr++ = ft_substr(s, 0, i - s);
		s = i;
	}
	return (ret);
}
