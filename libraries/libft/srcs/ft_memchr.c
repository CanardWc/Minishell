/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:13:23 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/28 15:40:11 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (--n > 0 && *(unsigned char *)s != (unsigned char)c)
		s++;
	return ((n == 0 && *(unsigned char *)s != (unsigned char)c) ? \
			NULL : (void *)s);
}
