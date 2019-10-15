/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 21:19:12 by eviana            #+#    #+#             */
/*   Updated: 2018/11/26 22:56:14 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long int newnb;

	newnb = n;
	if (n < 0)
	{
		ft_putchar('-');
		newnb = -newnb;
	}
	if (newnb >= 10)
		ft_putnbr(newnb / 10);
	ft_putchar((newnb % 10) + '0');
}
