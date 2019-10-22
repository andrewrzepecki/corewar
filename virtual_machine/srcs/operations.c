/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:40:47 by eviana            #+#    #+#             */
/*   Updated: 2019/10/22 20:34:28 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int		op_live(t_vm *vm, t_process *proc)
{
	int		id;
	
	id = read_address(vm, (proc->pc + 1) % MEM_SIZE, 4);
	if (id > 0 && id < vm->nb_players) // a voir si concordant avec notre traitement des ids // sinon faire une fonction is_valid_player()
	{
		ft_printf("Player %s (%d) is alive!\n", vm->player[id].name, id);
		vm->player[id].last_live = vm->cycles;
		proc->last_live = vm->cycles;
	}
	else
		ft_printf("Player with id %d doesn't exist: error\n", id);
	return (5); // on passe l'op_code et le dir(4);
}

int		op_ld(t_vm *vm, t_process *proc)
{
	t_param params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset); // en esperant que set_params marche bien quand il n'y a que 2 params
	if (is_valid_reg(params.n[1]))
	{
		proc->reg[params.n[1]] = params.n[0];
		if (proc->reg[params.n[0]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);
}

int		op_zjmp(t_vm *vm, t_process *proc)
{
	if (proc->carry)
		return (read_address(vm, (proc->pc + 1) % MEM_SIZE, 2)); // En sortie il faudra appliquer le % MEM_SIZE, on peut le faire en utilisant move_pc
	else
		return (3); // 1 + 2 : on passe l'opcode, puis on passe le D2
}

int		op_ldi(t_vm *vm, t_process *proc)
{
	t_param	params;
	int		offset; // Nous permet de savoir de combien de case avancer jusqu'à la fin de l'instruction
	
	params = set_params(vm, proc, proc->pc, &offset);
	if (is_valid_reg(params.n[2]))
	{
		proc->reg[params.n[2]] = read_address(vm, rel_address(proc, params.n[0], params.n[1]), 4);
		if (proc->reg[params.n[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);
}

int		op_sti(t_vm *vm, t_process *proc)
{
	t_param	params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset);
	if (is_valid_reg(params.n[0]))
	{
		vm->mem[rel_address(proc, params.n[1], params.n[2])] = proc->reg[params.n[0]];
		if (proc->reg[params.n[0]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);
}