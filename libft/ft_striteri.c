/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrzepec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:42:16 by anrzepec          #+#    #+#             */
/*   Updated: 2018/11/09 14:34:42 by anrzepec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int c;

	if (s && f)
	{
		c = -1;
		while (s[++c])
			(*f)(c, &s[c]);
	}
}
