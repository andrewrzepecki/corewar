/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:35:14 by eviana            #+#    #+#             */
/*   Updated: 2018/11/16 21:17:07 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t ldst;
	size_t lsrc;
	size_t j;

	ldst = ft_strlen((char*)dst);
	lsrc = ft_strlen((char*)src);
	j = 0;
	while (src[j] != '\0' && (ldst + j < n - 1) && n != 0)
	{
		dst[ldst + j] = src[j];
		j++;
	}
	if (j != 0)
		dst[ldst + j] = '\0';
	if (n < ldst)
		return (n + lsrc);
	else
		return (ldst + lsrc);
}
