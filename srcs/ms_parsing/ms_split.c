/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:21:07 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:21:15 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_arr_size(const char *s)
{
	size_t	l;

	l = 0;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		if (*s && *s != ' ')
			l++;
		while (*s && *s != ' ')
		{
			if (ft_strchr("\'\"", *s))
				s = ft_strchr(s + 1, *s);
			s++;
		}
	}
	return (l);
}

static int	ms_count_line(const char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (ft_strchr("\'\"", s[i]))
		{
			c = s[i++];
			while (s[i] && s[i] != c)
				i++;
		}
		i++;
	}
	return (i);
}

char	**ms_split(const char *s)
{
	char	**ret;
	char	**arr;
	int		i;

	if (!s)
		return (0);
	arr = (char **)ft_calloc(ft_arr_size(s) + 1, sizeof(char *));
	if (!arr)
		return (0);
	ret = arr;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		i = ms_count_line(s);
		if (*s)
			*arr++ = ft_substr(s, 0, i);
		s += i;
	}
	return (ret);
}
