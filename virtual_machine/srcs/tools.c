/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:49:41 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/21 12:49:44 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int			read_bytes(unsigned char *mem, size_t size)
{
	size_t bytes;
	int res;

	bytes = 0;
	res = 0;
	while (bytes < size)
	{
		res += mem[bytes] * ft_power(256, (4 - (bytes + 1)));
		bytes++;
	}
	return (res);
}