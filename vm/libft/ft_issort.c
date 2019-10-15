/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:03:14 by eviana            #+#    #+#             */
/*   Updated: 2019/04/11 19:07:33 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_issort(int *tab, int length, int (*f)(int, int))
{
	int i;

	i = 0;
	while (i < length - 2)
	{
		if ((f(tab[i], tab[i + 1]) >= 0 && f(tab[i + 1], tab[i + 2]) >= 0)
			|| (f(tab[i], tab[i + 1]) <= 0 && f(tab[i + 1], tab[i + 2]) <= 0))
			i++;
		else
			return (0);
	}
	return (1);
}
