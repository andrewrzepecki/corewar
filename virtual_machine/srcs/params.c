/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:33:09 by eviana            #+#    #+#             */
/*   Updated: 2019/10/22 18:45:52 by eviana           ###   ########.fr       */
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

int			get_param(t_vm *vm, t_process *proc, int pc, int code)
{
	int	dir_size;

	dir_size = (g_op_tab[proc->current_op - 1].dir_size ? 2 : 4);
	if (code == REG_CODE)
		return (proc->reg[read_address(vm, pc, 1)]);
	else if (code == DIR_CODE)
		return (read_address(vm, pc, dir_size));
	else if (code == IND_CODE) // attention, cela doit etre lu par rapport au pc initial et dépend de l'addressage restreint
	{
		if (g_op_tab[proc->current_op - 1].restr)
			return (read_address(vm, (proc->pc + (read_address(vm, pc, 2) % IDX_MOD)) % MEM_SIZE, 4));
		else
			return (read_address(vm, (proc->pc + read_address(vm, pc, 2)) % MEM_SIZE, 4));
	}
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

t_param		set_params(t_vm *vm, t_process *proc, int pc, int *offset) // opti avec l'offset à voir
{
	int			i;
	int			code;
	char		ocp;
	t_param     params;
	int			dir_size;

	i = 2;
	ocp = vm->mem[(pc + 1) % MEM_SIZE];
	pc = (pc + 2) % MEM_SIZE;
	*offset = 2; // 1 + 1 : on passera l'opcode puis l'ocp
	check_ocp(ocp); // Faire une action si nul : perror ?
	dir_size = (g_op_tab[proc->current_op - 1].dir_size ? 2 : 4);
	while (i >= 0)
	{
		ocp = ocp >> 2;
		code = get_code(ocp);
		params.n[i] = get_param(vm, proc, pc, code);
		pc = (pc + param_size(code, dir_size)) % MEM_SIZE;
		*offset = *offset + param_size(code, dir_size);
		i--;
	}
	return (params);
}