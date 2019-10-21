/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:36:52 by eviana            #+#    #+#             */
/*   Updated: 2019/10/21 18:38:12 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int		zjmp(t_vm *vm, int pc)
{
	//vm->time += 20; // Comment traiter la durée ?
	//move_pc(vm, proc_id, 1);
	if (vm->carry)
		return (read_address(vm, (pc + 1) % MEM_SIZE, 2)); // En sortie il faudra appliquer le % MEM_SIZE, on peut le faire en utilisant move_pc
	else
		return (3); // 1 + 2 : on passe l'opcode, puis on passe le D2
}

/*
**	Ne pas oublier de move_pc(vm, proc_id, 1) avant chaque fonction ==> NON
**  pour passer l'opcode et se retrouver soit sur l'ocp soit sur le 1er argument
**	Rajouter l'adressage restreint
*/

int			ldi(t_vm *vm, int pc)
{
	int     params[3];
	int		count; // Nous permet de savoir de combien de case avancer jusqu'a la fin de l'instruction
	
	//vm->time += 25; // Comment traiter la durée ?
	//move_pc(vm, proc_id, 1);
	params = set_params(vm, pc, &count, 2);
	vm->reg[params[2]] = read_address(vm, rel_address(vm, proc_id, params[0], params[1]));
	if (vm->reg[params[2]] == 0)
		vm->carry = 1;
	else
		vm->carry = 0;
	return (count);
}

int			sti(t_vm *vm, int proc_id)
{
	t_params	params;

	params = set_params(vm, proc_id);
	vm->mem[rel_address(vm, proc_id, params.n[1], params.n[2])] = vm->reg[params[0]];
	if (vm->reg[params[0]] == 0)
		vm->carry = 1;
	else
		vm->carry = 0;
	return (0);
}