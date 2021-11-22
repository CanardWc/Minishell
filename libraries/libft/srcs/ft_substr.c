/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:49:47 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/23 17:00:47 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	char	*dst;

	if (!s || !(dst = (char *)malloc((start >= len ? 1 : len + 1) \
					* sizeof(char))))
		return (NULL);
	ret = dst;
	if (start < len)
		while (s[start] && len--)
			*dst++ = s[start++];
	*dst = '\0';
	return (ret);
}
