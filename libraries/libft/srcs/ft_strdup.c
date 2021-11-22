/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:16:34 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/23 19:37:53 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s1)
{
	char	*ret;

	if (!(ret = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char))))
	   return (NULL);
	*(ret + ft_strlen(s1)) = 0;
	return (ft_memcpy(ret, s1, ft_strlen(s1)));
}
