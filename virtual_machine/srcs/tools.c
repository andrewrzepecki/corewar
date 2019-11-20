/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:49:41 by andrewrze         #+#    #+#             */
/*   Updated: 2019/11/20 20:39:25 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int		modulo_mem_size(int addr) // va prendre pc + offset / address semi absolue => renvoie addresse absolue
{
	if (addr >= 0)
		return (addr % MEM_SIZE);
	else
		return (MEM_SIZE + (addr % MEM_SIZE));
}

int		vegetable_garden(t_process *proc, int addr)
{
	// return (addr % IDX_MOD);
	// (void)proc;
	
	// addr = addr % IDX_MOD;
	// if (addr > (IDX_MOD / 2))
	// 	addr = - (IDX_MOD - addr);
	// return (addr);
	// (void)proc;
	

	
	// bouclage = rel_addr % MEM_SIZE;

	// new_absolute = (pc + bouclage) % MEM_SIZE = (pc + rel_addr) % MEM_SIZE;

	// decalage = new_absolute - pc

	// decalage = decalage % IDX_MOD

	
	/* OLD SHIT */
	// int restr_addr;
	// int	new_addr;

	// restr_addr = addr % IDX_MOD;
	
	// if (restr_addr >= IDX_MOD / 2) // TEST EN COURS
	// 	restr_addr = - IDX_MOD + restr_addr;

	// new_addr = (proc->pc + restr_addr) % MEM_SIZE;
	// if (new_addr < 0)
	// 	new_addr = MEM_SIZE + new_addr;

	// return (new_addr);
	// return (modulo_mem_size(proc->pc + (addr % IDX_MOD)));

	// NEW
	return ((((proc->pc + addr) % MEM_SIZE) - proc->pc) % IDX_MOD);
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

void        init_registers(t_process *process)
{
    int i;
	static int id = -1;

    i = 2;
	process->reg[0] = 0; // par securité mais il n'y a rien a cette valeur
    process->reg[1] = id--;
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

int			long_rel_address(t_process *proc, int add1, int add2) // sans adressage restreint
{
	return (modulo_mem_size(proc->pc + add1 + add2));
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
	unsigned to_write_uns;

	bytes = 0;
	to_write_uns = (unsigned int)to_write;
	// to_write_uns = to_write;

	// if (to_write < 0)
	// 	to_write_uns = _MAX_UNS_INT_ + to_write + 1;
	while (bytes < 4)
	{
		chunk = ft_power(256, (4 - (bytes + 1)));
		vm->mem[(addr + bytes) % MEM_SIZE] = to_write_uns / chunk;
		vm->owner[(addr + bytes) % MEM_SIZE] = -proc->master;
		to_write_uns = to_write_uns % chunk;
		bytes++;
	}
}