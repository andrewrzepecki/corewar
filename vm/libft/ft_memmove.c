/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:50:49 by eviana            #+#    #+#             */
/*   Updated: 2018/11/16 23:03:41 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*str;
	const char	*str2;

	str = (char*)dst;
	str2 = (const char*)src;
	if (dst < src)
		ft_memcpy(dst, src, n);
	else if (dst > src)
	{
		while (n != 0)
		{
			str[n - 1] = str2[n - 1];
			n--;
		}
	}
	return (dst);
}
