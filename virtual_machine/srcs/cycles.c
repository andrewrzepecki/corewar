/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:58:15 by eviana            #+#    #+#             */
/*   Updated: 2019/10/21 23:08:52 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int     op_dispatch(t_vm *vm, t_process *proc, int op_code)
{
	char	*(*op[16])(t_vm*, t_process*);
    int     offset;

	// op[0] = &op_live;
	// op[1] = &op_ld;
	// op[2] = &op_st;
	// op[3] = &op_add;
	// op[4] = &op_sub;
	// op[5] = &op_and;
	// op[6] = &op_or;
	// op[7] = &op_xor;
    // op[8] = &op_zjmp;
	// op[9] = &op_ldi;
	// op[10] = &op_sti;
	// op[11] = &op_fork;
	// op[12] = &op_lld;
	// op[13] = &op_lldi;
	// op[14] = &op_lfork;
	// op[15] = &op_aff;
    offset = op[op_code - 1](vm, proc);
	return (offset);
}

void    get_next_op(t_vm *vm, t_process *proc, int offset)
{
    proc->pc = proc->pc + offset % MEM_SIZE;
    while ()
    {
        
    }
}

void    update_process(t_vm *vm, t_process *proc)
{
    int offset;
    
    if (proc->current_op <= 0 || proc->current_op > 16)
        
    else if (proc->current_op == vm->mem[proc->pc])
    {
        offset = op_dispatch(vm, proc, vm->mem[proc->pc]);
        get_next_op(vm, proc, offset);
    }
    else
    {
        
    }
}

void    process_review(t_vm *vm)
{
    t_process   *current;

    current = vm->process;
    while (current)
    {
        if (!current->cycles_left)
            update_process(vm, current);
        else // check de validité de l'opcode ici ?
            current->cycles_left--;
        current = current->next;
    }
}

void    cycles(t_vm *vm)
{
    while (1) // change for until players left
    {
        process_review(vm);
        if (vm->vis != -1 && !(vm->cycles % vm->vis))
        {
            print_arena(vm);
            sleep(10);
        }
        vm->cycles++;
    }
}