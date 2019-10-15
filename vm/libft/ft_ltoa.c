/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:03:07 by eviana            #+#    #+#             */
/*   Updated: 2019/03/04 09:37:37 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	st_countsize(long int n)
{
	int i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*st_set_str(char *str, long newnb, int i, int limitmemory)
{
	while (newnb != 0)
	{
		str[i - 1] = (newnb % 10) + '0' + limitmemory;
		limitmemory = 0;
		newnb = newnb / 10;
		i--;
	}
	return (str);
}

char		*ft_ltoa(long int n)
{
	char			*str;
	long int		newnb;
	int				limitmemory;
	int				i;

	limitmemory = 0;
	newnb = n;
	i = st_countsize(n);
	if (!(str = ft_strnew(i)))
		return (NULL);
	if (n < 0 && newnb >= -9223372036854775807)
	{
		newnb = -newnb;
		str[0] = '-';
	}
	else if (n < 0 && newnb < -9223372036854775807)
	{
		newnb = -(newnb + 1);
		str[0] = '-';
		limitmemory = 1;
	}
	if (n == 0)
		str[0] = '0';
	str = st_set_str(str, newnb, i, limitmemory);
	return (str);
}
