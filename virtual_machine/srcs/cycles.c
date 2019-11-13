/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:58:15 by eviana            #+#    #+#             */
/*   Updated: 2019/11/13 20:06:52 by eviana           ###   ########.fr       */
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
	// op[15] = &op_aff;
    ft_printf("cycle %d : opcode %d pour proc %d\n", vm->cycles, op_code, proc->id);
	return (op[op_code - 1](vm, proc));
    //return(0);
}

void    get_cycles_left(t_process *proc)
{
    if (is_valid_op(proc->current_op))
        proc->cycles_left = g_op_tab[proc->current_op - 1].cycles;
    else // useless, ici pour la compréhension
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
    
    if (proc->current_op != vm->mem[proc->pc]) // si on a changé d'opcode durant les cycles d'attentes : on prend le nouvel op code et on reset l'attente !
        set_current_op(vm, proc);
    else if (!is_valid_op(proc->current_op)) // si opcode invalide on avance d'un et on laisse le cycle_left à 0
    {
        proc->pc = (proc->pc + 1) % MEM_SIZE;
        set_current_op(vm, proc);
    }
    else // si on voit toujours le meme opcode valide que celui enregistré on avance en fonctions des operations
    {
        offset = op_dispatch(vm, proc, proc->current_op); // les operations doivent retourner l'offset même si les params sont invalides
        proc->pc = (proc->pc + offset) % MEM_SIZE;
        set_current_op(vm, proc);
    }
}

void    process_review(t_vm *vm)
{
    t_process   *current;

    current = vm->process;
    //ft_printf("Process review 1, addresse vm->process : %p\n", vm->process);
    while (current)
    {
        if (!current->cycles_left || current->current_op != vm->mem[current->pc])
            update_process(vm, current);
        else
            current->cycles_left--;
        current = current->next;
    }
    //ft_printf("Process review 2, addresse vm->process : %p\n", vm->process);
}

t_process   *list_pop(t_vm *vm)
{
    t_process   *first;

    first = vm->process;
    vm->process = vm->process->next;
    free(first);
    return (vm->process);
}

t_process   *list_delone(t_process *prec, t_process *current)
{
    prec->next = current->next;
    free(current);
    return (prec);
}

int     life_check(t_vm *vm)
{
    t_process   *current;
    t_process   *prec;

    current = vm->process;
    prec = vm->process;
    while (current)
    {
        if (current->last_live <= vm->last_verif)
        {
            if (current == vm->process)
                current = list_pop(vm);
            else
                current = list_delone(prec, current);
        }
        prec = current;
        current = current->next;
    }
    if (vm->process == NULL || vm->process->next == NULL)
    {
        if (vm->process == NULL)
            ft_printf("TOUT LE MONDE EST MORT\n"); // TEST
        else
            ft_printf("LE DERNIER DES MOHICANS EST %d, son maitre est \"%d\"\n", vm->process->id, vm->process->master);
        return (END_GAME);
    }
    /* garder une valeur de retour pour la condition d'arrêt du while de cycles() ? 
    ** ex : si plus qu'un ou moins en vie, return 0
    */
    return (0);
}

int    cycles(t_vm *vm)
{
    while (1) // trouver condition d'arrêt, quand il ne reste plus qu'un joueur en vie ?
    {
       // if (cycles_check(vm))
       //     return(END_GAME);
        if ((vm->cycles != 0 && !((vm->cycles - vm->last_verif) % vm->cycles_to_die)) || vm->cycles_to_die <= 0) // à changer pour prendre en compte l'évolution de cycles_to_die
        {
            if (life_check(vm) == END_GAME) // sortie si tous mort ?
                return (END_GAME);
            if (++(vm->nb_checks) == MAX_CHECKS || vm->lives_since_check >= NBR_LIVE)
            {
                vm->cycles_to_die -= CYCLE_DELTA;
                vm->nb_checks = 0;
            }
            vm->last_verif = vm->cycles;
            vm->lives_since_check = 0;
        }
        ft_printf("Cycle : %d\n", vm->cycles);
        process_review(vm);
        //ft_printf("Review faite\n");
        if (vm->vis != -1 && !(vm->cycles % vm->vis))
        {
            print_arena(vm);
            sleep(1);
        }
        vm->cycles++;
    }
    return (END_GAME); // ?
}