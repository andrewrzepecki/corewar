/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:33:09 by eviana            #+#    #+#             */
/*   Updated: 2019/11/14 16:13:51 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int			get_t_code(char ocp)
{
	if ((ocp & 1) && ((ocp >> 1) & 1))
		return (T_IND);
	else if ((ocp >> 1) & 1)
		return (T_DIR);
	else if (ocp & 1)
		return (REG_CODE);
	else
		return (0);
}

int			check_ocp(t_process *proc, char ocp) // A FINIR
{
	int i;
	int param;

	i = 0;
	if ((ocp & 1) || (ocp >> 1) & 1)
		return (0);
	while (i < g_op_tab[proc->current_op - 1].params)
	{
		param = ocp >> (6 - (2 * i));
		if (!(get_t_code(param) & g_op_tab[proc->current_op - 1].type[i]))
			return (0);
		i++;	
	}
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
	{
		if (is_valid_reg(read_address(vm, pc, 1)))
			return (read_address(vm, pc, 1));
		else
			return (-1);
	}
	else if (code == DIR_CODE)
		return (read_address(vm, pc, dir_size));
	else if (code == IND_CODE)
	{
		if (g_op_tab[proc->current_op - 1].restr)
		{
			// ft_printf("coef = %d\n", coef);
			// ft_printf("IDX_MOD / 2 = %d\n", IDX_MOD / 2);
			// ft_printf("(coef %% ((IDX_MOD / 2) + coef)) : %d\n", coef % ((IDX_MOD / 2) + coef));
			// ft_printf("(coef %% (IDX_MOD / 2)) : %d\n", coef % (IDX_MOD / 2));
			// exit(0);
			// if (proc->id == 1)
			// {
			// 	idx = read_address(vm,pc, 2) % IDX_MOD;
			// 	ft_printf("proc->pc = %d\n", proc->pc);
			// 	ft_printf("(read_address(vm, pc, 2) = %d\n", read_address(vm, pc, 2));
			// 	ft_printf("proc->pc + (read_address(vm, pc, 2) %% IDX_MOD)) %% MEM_SIZE = %d\n", ((proc->pc + read_address(vm, pc, 2)) % (IDX_MOD + proc->pc + read_address(vm, pc, 2))) % MEM_SIZE);
			// 	exit(0);
			// }
			// return ((proc->pc + (read_address(vm, pc, 2) % IDX_MOD)) % MEM_SIZE);
			// return (((proc->pc + read_address(vm, pc, 2)) % IDX_MOD) % MEM_SIZE);
			return (vegetable_garden(proc, read_address(vm, pc, 2)));
			//return ((coef % ((IDX_MOD / 2) + proc->pc)) % MEM_SIZE);
			//return (coef % MEM_SIZE);
		}
		else
			return ((proc->pc + read_address(vm, pc, 2)) % MEM_SIZE);
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
	char		ocp;
	t_param     params;
	int			dir_size;

	i = 0;
	ocp = vm->mem[(pc + 1) % MEM_SIZE];
	pc = (pc + 2) % MEM_SIZE;
	*offset = 2; // 1 + 1 : on passera l'opcode puis l'ocp
	params.valid = 1;
	if (!check_ocp(proc, ocp)) // ATTENTION : A VOIR
		params.valid = 0; // Faire une action si nul : perror ?
	dir_size = (g_op_tab[proc->current_op - 1].dir_size ? 2 : 4);
	while (i < 3)
	{
		//ocp = ocp >> 2; // ocp >> (6 - (2 * i))
		params.c[i] = get_code(ocp >> (6 - (2 * i)));
		if ((params.n[i] = get_param(vm, proc, pc, params.c[i])) == -1)
			params.valid = 0;
		pc = (pc + param_size(params.c[i], dir_size)) % MEM_SIZE;
		*offset = *offset + param_size(params.c[i], dir_size);
		i++;
	}
	return (params);
}