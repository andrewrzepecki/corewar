/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/10/15 21:40:00 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

int			read_address(t_vm *vm, int address)
{
	int		res;
	size_t	bytes;

	bytes = 4;
	while (bytes)
	{
		res = vm->mem[address] * ft_power(256, bytes - 1);
		address = (address + 1) % MEM_SIZE;
		bytes--;
	}
	return (res);
}

int			read_bytes(t_vm *vm, int proc_id, size_t bytes)
{
	int		res;

	res = 0;
	while (bytes)
	{
		res = vm->mem[vm->proc[proc_id].pc] * ft_power(256, bytes - 1);
		move_pc(vm, proc_id, 1);
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

int			get_param(t_vm *vm, int proc_id, int code)
{
	if (code == REG_CODE)
		return (vm->reg[read_bytes(vm, proc_id, 1)]);
	else if (code == DIR_CODE)
		return (read_bytes(vm, proc_id, 2));
	else if (code == IND_CODE)
		return (read_address(vm, read_bytes(vm, proc_id, 2)));
	return (0);
}

t_params	set_params(t_vm *vm, int proc_id)
{
	int			i;
	char		ocp;
	t_params 	params;

	i = 0;
	ocp = vm->mem[vm->proc[proc_id].pc];
	check_ocp(ocp); // Faire une action si nul : perror ?
	move_pc(vm, proc_id, 1);
	while (i < 3)
	{
		ocp = ocp >> 2;
		params.n[i] = get_param(vm, proc_id, get_code(ocp));
		i++;
	}
	return (params);
}

int		zjmp(t_vm *vm, int proc_id)
{
	//vm->time += 20; // Comment traiter la durée ?
	//move_pc(vm, proc_id, 1);
	if (vm->carry)
		move_pc(vm, proc_id, read_bytes(vm, proc_id, 2));
	else
		move_pc(vm, proc_id, 2);
	return (0); // On est déjà où on le souhaite
}

/*
**	Ne pas oublier de move_pc(vm, proc_id, 1) avant chaque fonction
*/

int			ldi(t_vm *vm, int proc_id)
{
	t_params	params;
	
	//vm->time += 25; // Comment traiter la durée ?
	//move_pc(vm, proc_id, 1);
	params = set_params(vm, proc_id);
	vm->reg[params.n[2]] = read_address(vm, params.n[0] + params.n[1]);
	return (1); // On doit encore décaler de 1;
}