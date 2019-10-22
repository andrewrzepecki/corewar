/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:49:41 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/22 19:57:26 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int			is_valid_reg(int reg)
{
	if (reg > 0 && reg < 17)
		return (1);
	return (0);
}

int			rel_address(t_process *proc, int add1, int add2)
{
	return ((proc->pc + ((add1 + add2) % IDX_MOD)) % MEM_SIZE);
}

int			read_address(t_vm *vm, int pc, size_t bytes)
{
	int		res;

	while (bytes)
	{
		res = vm->mem[pc] * ft_power(256, bytes - 1);
		pc = (pc + 1) % MEM_SIZE;
		bytes--;
	}
	return (res);
}

int			read_bytes(unsigned char *mem, size_t size) // attention a l'overflow
{
	size_t bytes;
	int res;

	bytes = 0;
	res = 0;
	while (bytes < size)
	{
		res += mem[bytes] * ft_power(256, (4 - (bytes + 1))); // peut overflow
		bytes++;
	}
	return (res);
}