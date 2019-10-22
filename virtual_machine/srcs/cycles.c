/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:58:15 by eviana            #+#    #+#             */
/*   Updated: 2019/10/22 15:14:39 by eviana           ###   ########.fr       */
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

int     is_valid_op(int op_code)
{
    if (op_code <= 0 || op_code > 16)
        return (0);
    else
        return (1);
}

void    get_cycles_left(t_process *proc)
{
    if (is_valid_op(proc->current_op))
        proc->cycles_left = g_op_tab[proc->current_op].cycles;
    else // useless, ici pour la conpréhension
        proc->cycles_left = 0;
}

void    set_current_op(t_vm *vm, t_process *proc)
{
    proc->current_op = vm->mem[proc->pc];
    get_cycles_left(proc);
}

void    update_process(t_vm *vm, t_process *proc)
{
    int offset;
    
    if (!is_valid_op(proc->current_op)) // si opcode invalide on avance d'un et on laisse le cycle_left à 0
    {
        proc->pc = (proc->pc + 1) % MEM_SIZE;
        set_current_op(vm, proc);
    }
    else if (proc->current_op == vm->mem[proc->pc]) // si on voit toujours le meme opcode valide que celui enregistré on avance en fonctions des operations
    {
        offset = op_dispatch(vm, proc, proc->current_op); // les operations doivent retourner l'offset même si les params sont invalides
        proc->pc = (proc->pc + offset) % MEM_SIZE;
        set_current_op(vm, proc);
    }
    else // si on a changé d'opcode durant les cycles d'attentes et qu'il est valide, on prend le nouvel op code et on reset l'attente ?
        set_current_op(vm, proc);
}

void    process_review(t_vm *vm)
{
    t_process   *current;

    current = vm->process;
    while (current)
    {
        if (!current->cycles_left)
            update_process(vm, current);
        else // doit-on checker aussi la validité de l'opcode ici ?
            current->cycles_left--;
        current = current->next;
    }
}

void    life_check(t_vm *vm)
{
    t_process   *current;

    current = vm->process;
    while (current)
    {
        // if toujours en vie => process continue
        // if pas de vie, retirer de la liste des process
        current = current->next;
    }
    /* garder une valeur de retour pour la condition d'arret du while de cycles() ? 
    ** ex : si plus qu'un ou moins en vie, return 0
    */
}

void    cycles(t_vm *vm)
{
    while (1) // trouver condition d'arret, quand il ne reste plus qu'un joueur en vie ?
    {
        if (vm->cycles != 0 && !(vm->cycles % CYCLE_TO_DIE))
            life_check(vm);
        process_review(vm);
        if (vm->vis != -1 && !(vm->cycles % vm->vis))
        {
            print_arena(vm);
            sleep(10);
        }
        vm->cycles++;
    }
}