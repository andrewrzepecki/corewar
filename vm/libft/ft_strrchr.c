/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 22:36:42 by eviana            #+#    #+#             */
/*   Updated: 2018/11/09 13:45:47 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	rc;
	char	*str;

	str = (char*)s;
	rc = (char)c;
	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != rc && i != 0)
		i--;
	if (str[i] == rc)
		return (&str[i]);
	else
		return (NULL);
}
