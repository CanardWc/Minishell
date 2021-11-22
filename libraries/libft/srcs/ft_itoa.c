/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:24:17 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/28 13:11:37 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_itoa(int n)
{
	char		*dest;
	int		size;
	unsigned int	nb;

	nb = n < 0 ? n * -1 : n;
	size = (n < 0 ? 1 : 0);
	while ((nb /= 10) > 0)
		size++;
	if (!(dest = (char *)ft_calloc(size + 2, sizeof(char))))
		return (0);
	nb = n < 0 ? n * -1 : n;
	dest[size--] = (nb % 10) + 48;
	while ((nb /= 10) > 0)
		dest[size--] = (nb % 10) + 48;
	if (size == 0)
		dest[0] = '-';
	return (dest);
}
