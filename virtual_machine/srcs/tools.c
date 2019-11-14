/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:49:41 by andrewrze         #+#    #+#             */
/*   Updated: 2019/11/14 16:26:03 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int		vegetable_garden(t_process *proc, int addr)
{
	int restr_addr;
	int	new_addr;

	restr_addr = addr % IDX_MOD;
	// ft_printf("restr_addr = %d\n", restr_addr);
	if (restr_addr > IDX_MOD / 2)
		restr_addr = - IDX_MOD + restr_addr;
	new_addr = proc->pc + restr_addr;
	if (new_addr < 0)
		new_addr = MEM_SIZE + new_addr;
	// ft_printf("new_addr = %d\n", new_addr);
	// exit(0);
	return (new_addr);
}

void	param_dump(t_param params)
{
	int i;

	i = 0;
	ft_printf("param valid : %d\n", params.valid);
	while (i < 3)
	{
		ft_printf("params[%d] type : %d | value : %d\n", i, params.c[i], params.n[i]);
		i++;
	}
	exit(0);
}

int     is_valid_op(int op_code)
{
    if (op_code <= 0 || op_code > 16)
        return (0);
    else
        return (1);
}

int			is_valid_reg(int reg)
{
	if (reg > 0 && reg < 17)
		return (1);
	return (0);
}

void        init_registers(t_process *process, t_player player)
{
    int i;

    i = 2;
	process->reg[0] = 0; // par securité mais il n'y a rien a cette valeur
    process->reg[1] = player.id;
    while (i < 17)
    {
        process->reg[i] = 0;
        i++;
    }
}

void        copy_registers(t_process *new, t_process *proc)
{
    int i;

    i = 1;
	new->reg[0] = 0;
    while (i < 17)
    {
        new->reg[i] = proc->reg[i];
        i++;
    }
}

int			rel_address(t_process *proc, int add1, int add2) // avec adressage restreint
{
	return (vegetable_garden(proc, add1 + add2));
	//return ((proc->pc + ((add1 + add2) % IDX_MOD)) % MEM_SIZE);
}

int			long_rel_address(t_process *proc, int add1, int add2) // sans adressage restreint
{
	return ((proc->pc + add1 + add2) % MEM_SIZE);
}

int			read_address(t_vm *vm, int addr, size_t bytes)
{
	int		res;

	res = 0;
	while (bytes)
	{
		res += vm->mem[addr] * ft_power(256, bytes - 1);
		addr = (addr + 1) % MEM_SIZE;
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

void		write_to_address(t_vm *vm, t_process *proc, int addr, int to_write)
{
	int	bytes;
	int chunk;

	bytes = 0;
	while (bytes < 4)
	{
		chunk = ft_power(256, (4 - (bytes + 1)));
		vm->mem[(addr + bytes) % MEM_SIZE] = to_write / chunk;
		vm->owner[(addr + bytes) % MEM_SIZE] = proc->master;
		to_write = to_write % chunk;
		bytes++;
	}
}