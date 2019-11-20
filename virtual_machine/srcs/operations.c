/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:40:47 by eviana            #+#    #+#             */
/*   Updated: 2019/11/20 19:56:10 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
** A REVOIR EN PRENANT EN COMPTE LE FAIT QUE LES PARAMS REMONTENT 
** LES ADRESSES DES INDIRECTS ET PAS LA VALEUR CONTENUE DEDANS
*/

int		op_live(t_vm *vm, t_process *proc)
{
	int 	i;
	int		id;
	
	i = 0;
	id = read_address(vm, (proc->pc + 1) % MEM_SIZE, 4);
	while (i < vm->nb_players)
	{
		if (id == vm->player[i].id) // ou -id == vm->player[i].id
		{
			//if (vm->verbose == 1)
				//ft_printf("Player %s (%d) is alive!\n", vm->player[i].name, id);
			vm->player[i].last_live = vm->cycles;
			vm->last_live = &vm->player[i];
		}
		i++;
	}
	//vm->last_live = &vm->player[id]; // segfault
	proc->last_live = vm->cycles;
	//else
		//ft_printf("Player with id %d doesn't exist: error\n", id);
	vm->lives_since_check++;
	return (5); // on passe l'op_code et le dir(4);
}

int		op_ld(t_vm *vm, t_process *proc)
{
	t_param params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset); // en esperant que set_params marche bien quand il n'y a que 2 params
	if (params.valid) // anciennement : if (is_valid_reg(params.n[1]))
	{
		if (params.c[0] == IND_CODE)
			params.n[0] = read_address(vm, params.n[0], 4);
		proc->reg[params.n[1]] = params.n[0];
		if (proc->reg[params.n[1]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);
}

int		op_st(t_vm *vm, t_process *proc)
{
	t_param	params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset);
	// param_dump(params);
	if (params.valid)
	{
		if (params.c[1] == IND_CODE)
		{
			//params.n[1] = read_address(vm, params.n[1], 4); // NEW NEW NEW !!!
			//write_to_address(vm, proc, vegetable_garden(proc, params.n[1]), proc->reg[params.n[0]]);
			write_to_address(vm, proc, params.n[1], proc->reg[params.n[0]]);
		}
		else if (params.c[1] == REG_CODE)
			proc->reg[params.n[1]] = proc->reg[params.n[0]];
		// if (proc->reg[params.n[0]] == 0)
		// 	proc->carry = 1;
		// else
		// 	proc->carry = 0;
	}
	return (offset);
}

int		op_add(t_vm *vm, t_process *proc)
{
	t_param params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset);
	if (params.valid)
	{
		//ft_printf("params.n[0] : %d\n", params.n[0]); // TEST
		//ft_printf("params.n[1] : %d\n", params.n[1]); // TEST
		//ft_printf("params.n[2] : %d\n", params.n[2]); // TEST
		//printf("Problem = %d\n", proc->reg[params.n[0]] + proc->reg[params.n[1]]); // TEST TEST TEST A VIRER
		proc->reg[params.n[2]] = proc->reg[params.n[0]] + proc->reg[params.n[1]]; // et si il y a overflow, si l'addition depasse un int ?
		if (proc->reg[params.n[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);
}

int		op_sub(t_vm *vm, t_process *proc)
{
	t_param params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset);
	if (params.valid)
	{
		proc->reg[params.n[2]] = proc->reg[params.n[0]] - proc->reg[params.n[1]]; // et si il y a overflow, si l'addition depasse un int ?
		if (proc->reg[params.n[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);	
}

int		op_and(t_vm *vm, t_process *proc)
{
	t_param params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset);
	if (params.valid)
	{
		if (params.c[0] == REG_CODE)
			params.n[0] = proc->reg[params.n[0]];
		else if (params.c[0] == IND_CODE)
			params.n[0] = read_address(vm, params.n[0], 4);
		if (params.c[1] == REG_CODE)
			params.n[1] = proc->reg[params.n[1]];
		else if (params.c[1] == IND_CODE)
			params.n[1] = read_address(vm, params.n[1], 4);
		proc->reg[params.n[2]] = params.n[0] & params.n[1];
		if (proc->reg[params.n[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);
}

int		op_or(t_vm *vm, t_process *proc)
{
	t_param params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset);
	if (params.valid)
	{
		if (params.c[0] == REG_CODE)
			params.n[0] = proc->reg[params.n[0]];
		else if (params.c[0] == IND_CODE)
			params.n[0] = read_address(vm, params.n[0], 4);
		if (params.c[1] == REG_CODE)
			params.n[1] = proc->reg[params.n[1]];
		else if (params.c[1] == IND_CODE)
			params.n[1] = read_address(vm, params.n[1], 4);
		proc->reg[params.n[2]] = params.n[0] | params.n[1];
		if (proc->reg[params.n[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);
}

int		op_xor(t_vm *vm, t_process *proc)
{
	t_param params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset);
	if (params.valid)
	{
		if (params.c[0] == REG_CODE)
			params.n[0] = proc->reg[params.n[0]];
		else if (params.c[0] == IND_CODE)
			params.n[0] = read_address(vm, params.n[0], 4);
		if (params.c[1] == REG_CODE)
			params.n[1] = proc->reg[params.n[1]];
		else if (params.c[1] == IND_CODE)
			params.n[1] = read_address(vm, params.n[1], 4);
		proc->reg[params.n[2]] = params.n[0] ^ params.n[1];
		if (proc->reg[params.n[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);
}

int		op_zjmp(t_vm *vm, t_process *proc) // AVEC IDX_MOD ???
{
	// if (proc->carry)
	// 	ft_printf("Jump to: %d %d and pc = %d\n", vm->mem[(proc->pc + 1) % MEM_SIZE], vm->mem[(proc->pc + 2) % MEM_SIZE], proc->pc); // En sortie il faudra appliquer le % MEM_SIZE, on peut le faire en utilisant move_pc
	if (proc->carry)

		// SANS IDX_MOD
		// return (read_address(vm, (proc->pc + 1) % MEM_SIZE, 2));

		// AVEC IDX_MOD
		return (vegetable_garden(proc, read_address(vm, (proc->pc + 1) % MEM_SIZE, 2)));
		//return (read_address(vm, (proc->pc + 1) % MEM_SIZE, 2) % IDX_MOD);
	else
		return (3); // 1 + 2 : on passe l'opcode, puis on passe le D2
}

int		op_ldi(t_vm *vm, t_process *proc)
{
	t_param	params;
	int		offset; // Nous permet de savoir de combien de case avancer jusqu'à la fin de l'instruction
	
	params = set_params(vm, proc, proc->pc, &offset);
	if (params.valid) // anciennement : if (is_valid_reg(params.n[2]))
	{
		if (params.c[0] == REG_CODE)
			params.n[0] = proc->reg[params.n[0]];
		else if (params.c[0] == IND_CODE)
			params.n[0] = read_address(vm, params.n[0], 4);
		if (params.c[1] == REG_CODE)
			params.n[1] = proc->reg[params.n[1]];
		
		// AVEC VEGETABLE GARDEN
		proc->reg[params.n[2]] = read_address(vm, modulo_mem_size(proc->pc + vegetable_garden(proc, params.n[0] + params.n[1])), 4);

		// SANS VEGETABLE GARDEN
		// ft_printf("pc = %d | params.n[1] = %d | params.n[2] = %d | addr = %d\n", (proc->pc + (params.n[0] + params.n[1])) % MEM_SIZE);
		// proc->reg[params.n[2]] = read_address(vm, modulo_mem_size(proc->pc + (params.n[1] + params.n[2])), 4);

		// if (proc->reg[params.n[2]] == 0)
		// 	proc->carry = 1;
		// else
		// 	proc->carry = 0;
	}
	return (offset);
}

int		op_sti(t_vm *vm, t_process *proc)
{
	t_param	params;
	int		offset;


	params = set_params(vm, proc, proc->pc, &offset);
	if (params.valid) // anciennement : if (is_valid_reg(params.n[0]))
	{
		//vm->mem[rel_address(proc, params.n[1], params.n[2])] = proc->reg[params.n[0]]; // erreur car ne prend pas en compte les 4 octets ou ecrire
		if (params.c[1] == REG_CODE)
			params.n[1] = proc->reg[params.n[1]];
		else if (params.c[1] == IND_CODE)
			params.n[1] = read_address(vm, params.n[1], 4);
		if (params.c[2] == REG_CODE)
			params.n[2] = proc->reg[params.n[2]];
		
		// AVEC VEGETABLE GARDEN
		write_to_address(vm, proc, modulo_mem_size(proc->pc + vegetable_garden(proc, params.n[1] + params.n[2])), proc->reg[params.n[0]]);

		// SANS VEGETABLE GARDEN
		// write_to_address(vm, proc, modulo_mem_size(proc->pc + (params.n[1] + params.n[2])), proc->reg[params.n[0]]);

		// if (proc->reg[params.n[0]] == 0) // Certains disent non
		// 	proc->carry = 1;
		// else
		// 	proc->carry = 0;
	}

	return (offset);
}

int		op_fork(t_vm *vm, t_process *proc) // WORK IN PROGRESS
{
	t_process *new;

	if (!(new = (t_process*)malloc(sizeof(t_process))))
        return (-1); // comment gerer une erreur de malloc ici ? return (put_error() qui free le tout ?);
	new->id = vm->nb_proc++; // comment on gere les id de process ?
	new->master = proc->master;
    new->carry = proc->carry;


    // new->last_live = vm->cycles; // On met le cycle courant ?
	new->last_live = 0;

	//ft_printf("Where to be forked: %d\n", read_address(vm, (proc->pc + 1) % MEM_SIZE, 2));
    
	// !!!!! Sans IDX_MOD
	//new->pc = (proc->pc + read_address(vm, (proc->pc + 1) % MEM_SIZE, 2)) % MEM_SIZE; 
	
	// Avec IDX_MOD	
	new->pc = modulo_mem_size(proc->pc + vegetable_garden(proc, read_address(vm, (proc->pc + 1) % MEM_SIZE, 2)));
  
    new->current_op = vm->mem[new->pc];
	if (is_valid_op(new->current_op))
    	new->cycles_left = g_op_tab[new->current_op - 1].cycles - 1;
	else
		new->cycles_left = 0; // ou 1 ?
	copy_registers(new, proc);
	new->next = vm->process; // On push au debut de la file de process (revoir porentiellement comment on initialise la file de process)
	vm->process = new;
	return (3); // on sautera l'opcode + le D2;
}

int		op_lld(t_vm *vm, t_process *proc) // identique a op_ld car l'addressage restreint est pris en compte dans set_params / get_param
{
	t_param params;
	int		offset;

	params = set_params(vm, proc, proc->pc, &offset);
	if (params.valid)
	{
		if (params.c[0] == IND_CODE)
			params.n[0] = read_address(vm, params.n[0], 4);
		proc->reg[params.n[1]] = params.n[0];
		if (proc->reg[params.n[1]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);
}

int		op_lldi(t_vm *vm, t_process *proc)
{
	t_param	params;
	int		offset;
	
	params = set_params(vm, proc, proc->pc, &offset);
	if (params.valid )
	{
		if (params.c[0] == REG_CODE)
			params.n[0] = proc->reg[params.n[0]];
		else if (params.c[0] == IND_CODE)
			params.n[0] = read_address(vm, params.n[0], 4);
		if (params.c[1] == IND_CODE)
			params.n[1] = read_address(vm, params.n[1], 4);
		proc->reg[params.n[2]] = read_address(vm, modulo_mem_size(proc->pc + params.n[0] + params.n[1]), 4);
		if (proc->reg[params.n[2]] == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	return (offset);	
}

int		op_lfork(t_vm *vm, t_process *proc) // WORK IN PROGRESS
{
	t_process *new;

	if (!(new = (t_process*)malloc(sizeof(t_process))))
        return (-1); // comment gerer une erreur de malloc ici ? return (put_error() qui free le tout ?);
	new->id = vm->nb_proc++; // comment on gere les id de process ?
	new->master = proc->master;
    new->carry = proc->carry;


    // new->last_live = vm->cycles; // On met le cycle courant ?
	new->last_live = 0;


	new->pc = modulo_mem_size(proc->pc + read_address(vm, (proc->pc + 1) % MEM_SIZE, 2));

	// OLD
    // new->pc = (proc->pc + read_address(vm, (proc->pc + 1) % MEM_SIZE, 2)) % MEM_SIZE;
    
	new->current_op = vm->mem[new->pc];
	if (is_valid_op(new->current_op))
    	new->cycles_left = g_op_tab[new->current_op - 1].cycles - 1;
	else
		new->cycles_left = 0; // ou 1 ?
	copy_registers(new, proc);
	new->next = vm->process; // On push au debut de la file de process (revoir porentiellement comment on initialise la file de process)
	vm->process = new;
	return (3); // on sautera l'opcode + le D2;
}

int		op_aff(t_vm *vm, t_process *proc) // todo
{
	(void)vm;
	(void)proc;
	ft_printf("J'affiche !\n");
	return (2);
}