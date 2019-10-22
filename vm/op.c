/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/10/22 18:16:54 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 1},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 1},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 0},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 0},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0}
};

int			rel_address(t_vm *vm, int proc_id, int add1, int add2)
{
	return ((vm->proc[proc_id]->pc + ((add1 + add2) % IDX_MOD)) % MEM_SIZE);
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

void		move_pc(t_vm *vm, int proc_id, int offset)
{
	vm->proc[proc_id].pc = (vm->proc[proc_id].pc + offset) % MEM_SIZE;
}

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

t_params	set_params(t_vm *vm, int pc, int *count, int dir_size)
{
	int			i;
	int			code;
	char		ocp;
	t_params 	params;

	i = 0;
	ocp = vm->mem[(pc + 1) % MEM_SIZE];
	pc = (pc + 2) % MEM_SIZE;
	*count = 2; // 1 + 1 : on passera l'opcode puis l'ocp
	check_ocp(ocp); // Faire une action si nul : perror ?
	while (i < 3)
	{
		ocp = ocp >> 2;
		code = get_code(ocp);
		params.n[i] = get_param(vm, pc, code, dir_size);
		pc = (pc + param_size(code, dir_size)) % MEM_SIZE;
		*count = *count + param_size(code, dir_size);
		i++;
	}
	return (params);
}

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
	t_params	params;
	int			count; // Nous permet de savoir de combien de case avancer jusqu'a la fin de l'instruction
	
	//vm->time += 25; // Comment traiter la durée ?
	//move_pc(vm, proc_id, 1);
	params = set_params(vm, pc, &count, 2);
	vm->reg[params.n[2]] = read_address(vm, rel_address(vm, proc_id, params.n[0], params.n[1]));
	if (vm->reg[params.n[2]] == 0)
		vm->carry = 1;
	else
		vm->carry = 0;
	return (count);
}

int			sti(t_vm *vm, int proc_id)
{
	t_params	params;

	params = set_params(vm, proc_id);
	vm->mem[rel_address(vm, proc_id, params.n[1], params.n[2])] = vm->reg[params.n[0]];
	if (vm->reg[params.n[0]] == 0)
		vm->carry = 1;
	else
		vm->carry = 0;
	return (0);
}