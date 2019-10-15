/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 22:24:37 by eviana            #+#    #+#             */
/*   Updated: 2018/11/09 19:24:55 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	rc;
	char	*str;

	str = (char*)s;
	rc = (char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == rc)
			return (&str[i]);
		i++;
	}
	if (str[i] == '\0' && rc == 0)
		return (&str[i]);
	return (NULL);
}
