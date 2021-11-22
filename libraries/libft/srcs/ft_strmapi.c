/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:37:37 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/28 11:38:54 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char		*dst;
	unsigned char	i;

	if (!s || !(dst = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (s[i])
		(dst[i] = f(i, s[i]), i++);
	return (dst);
}
