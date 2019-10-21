/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:33:09 by eviana            #+#    #+#             */
/*   Updated: 2019/10/21 18:36:20 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int			check_ocp(char ocp)
{
	if ((ocp & 1) || (ocp >> 1) & 1)
		return (0); // OCP incorrect
	return (1);
}

int			get_code(char ocp)
{
	if ((ocp & 1) && ((ocp >> 1) & 1))
		return (IND_CODE);
	else if ((ocp >> 1) & 1)
		return (DIR_CODE);
	else if (ocp & 1)
		return (REG_CODE);
	else
		return (0);
}

int			get_param(t_vm *vm, int pc, int code, int dir_size)
{
	if (code == REG_CODE)
		return (vm->reg[read_address(vm, pc, 1)]);
	else if (code == DIR_CODE)
		return (read_address(vm, pc, dir_size));
	else if (code == IND_CODE)
		return (read_address(vm, read_address(vm, pc, 2), 4)); // attention, cela doit etre lu par rapport au pc initial et dépend de l'addressage restreint
	return (0);
}

int			param_size(int code, int dir_size)
{
	if (code == REG_CODE)
		return (1);
	else if (code == DIR_CODE)
		return (dir_size);
	else if (code == IND_CODE)
		return (2);
	return (0);
}

int     *set_params(t_vm *vm, int pc, int *count, int dir_size)
{
	int			i;
	int			code;
	char		ocp;
	int         params[3];

	i = 0;
	ocp = vm->mem[(pc + 1) % MEM_SIZE];
	pc = (pc + 2) % MEM_SIZE;
	*count = 2; // 1 + 1 : on passera l'opcode puis l'ocp
	check_ocp(ocp); // Faire une action si nul : perror ?
	while (i < 3)
	{
		ocp = ocp >> 2;
		code = get_code(ocp);
		params[i] = get_param(vm, pc, code, dir_size);
		pc = (pc + param_size(code, dir_size)) % MEM_SIZE;
		*count = *count + param_size(code, dir_size);
		i++;
	}
	return (params);
}