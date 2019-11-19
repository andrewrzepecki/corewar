/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_review.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:58:15 by eviana            #+#    #+#             */
/*   Updated: 2019/11/19 22:33:22 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int     op_dispatch(t_vm *vm, t_process *proc, int op_code)
{
	int     (*op[16])(t_vm*, t_process*);

	op[0] = &op_live;
	op[1] = &op_ld;
	op[2] = &op_st;
	op[3] = &op_add;
	op[4] = &op_sub;
	op[5] = &op_and;
	op[6] = &op_or;
	op[7] = &op_xor;
    op[8] = &op_zjmp;
	op[9] = &op_ldi;
	op[10] = &op_sti;
	op[11] = &op_fork;
	op[12] = &op_lld;
	op[13] = &op_lldi;
	op[14] = &op_lfork;
	op[15] = &op_aff;
    ft_printf("cycle %d : opcode %d pour proc %d\n", vm->cycles, op_code, proc->id);
    return (op[op_code - 1](vm, proc));
    //return(0);
}

void    get_cycles_left(t_process *proc)
{
    if (is_valid_op(proc->current_op))
        proc->cycles_left = g_op_tab[proc->current_op - 1].cycles - 1;
    else 
        proc->cycles_left = 0;
}

void    set_current_op(t_vm *vm, t_process *proc)
{
    proc->current_op = vm->mem[proc->pc];
    get_cycles_left(proc);
}

int    update_process(t_vm *vm, t_process *proc)
{
    int offset;
    
    if (proc->current_op != vm->mem[proc->pc]) // si on a changé d'opcode durant les cycles d'attentes : on prend le nouvel op code et on reset l'attente !
        set_current_op(vm, proc);
    else if (!is_valid_op(proc->current_op)) // si opcode invalide on avance d'un et on laisse le cycle_left à 0
    {
        // ft_printf("L'operation n'est pas valide : cycle = %d | pc = %d | c_op = %d\n", vm->cycles, proc->pc, proc->current_op);
        proc->pc = (proc->pc + 1) % MEM_SIZE;
        set_current_op(vm, proc);
    }
    else // si on voit toujours le meme opcode valide que celui enregistré on avance en fonctions des operations
    {
        if ((offset = op_dispatch(vm, proc, proc->current_op)) == -1)
            return (1);
        proc->pc = (proc->pc + offset) % MEM_SIZE;
        set_current_op(vm, proc);
    }
    return (0);
}

int    process_review(t_vm *vm, t_process *process)
{
    if (!process->cycles_left || process->current_op != vm->mem[process->pc])
    {
        if (update_process(vm, process))
            return (1);
    }
    else
        process->cycles_left--;
    return (0);
}