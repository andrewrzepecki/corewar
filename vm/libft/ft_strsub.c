/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:38:20 by eviana            #+#    #+#             */
/*   Updated: 2019/01/31 17:54:28 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s || !(str = ft_strnew(n)))
		return (NULL);
	while (i < n)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}
