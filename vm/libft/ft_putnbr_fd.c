/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 21:19:41 by eviana            #+#    #+#             */
/*   Updated: 2018/11/26 22:57:05 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int newnb;

	newnb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		newnb = -newnb;
	}
	if (newnb >= 10)
		ft_putnbr_fd((newnb / 10), fd);
	ft_putchar_fd((newnb % 10) + '0', fd);
}
