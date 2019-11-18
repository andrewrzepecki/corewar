/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_virtual_machine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:44:35 by andrewrze         #+#    #+#             */
/*   Updated: 2019/11/18 12:44:39 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void     cycle_review(t_vm *vm)
{
    if (++(vm->nb_checks) == MAX_CHECKS || vm->lives_since_check >= NBR_LIVE)
    {
        vm->cycles_to_die -= CYCLE_DELTA;
        vm->nb_checks = 0;
    }
    vm->last_verif = vm->cycles;
    vm->lives_since_check = 0;
}

int     option_review(t_vm *vm)
{
    if (vm->dump == vm->cycles)
    {
        print_arena(vm);
        return (END_GAME);
    }
    if (vm->cycles && vm->vis != -1 && !(vm->cycles % vm->vis))
    {
        print_arena(vm);
        sleep(1);
    }
    return (0);
}

int     machine_review(t_vm *vm)
{
    if (option_review(vm))
        return (END_GAME);
    if (vm->cycles && !((vm->cycles - vm->last_verif) % vm->cycles_to_die))
    {
        if (life_check(vm))
            return (END_GAME);
        cycle_review(vm);
    }
    return (0);
}

int     exec_machine(t_vm *vm)
{
    t_process *champion;

    while (machine_review(vm) != END_GAME)
    {
        champion = vm->process;
        while (champion)
        {
            if (process_review(vm, champion))
                return (ALLOC_ERROR);
            champion = champion->next;
        }
        vm->cycles++; // commencer a zero ou plutot 1?
    }
    return (END_GAME);
}