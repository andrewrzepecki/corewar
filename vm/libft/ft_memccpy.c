/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:48:21 by eviana            #+#    #+#             */
/*   Updated: 2018/11/16 21:56:06 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*str;
	unsigned const char	*str2;

	i = 0;
	str = (unsigned char*)dst;
	str2 = (unsigned const char*)src;
	while (i < n)
	{
		str[i] = str2[i];
		if (str2[i] == (unsigned char)c)
			return (&str[i + 1]);
		i++;
	}
	return (NULL);
}
