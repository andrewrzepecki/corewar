/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:58:15 by eviana            #+#    #+#             */
/*   Updated: 2019/11/15 16:57:30 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

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
        if (current)
            current = current->next;
    }
    if (vm->process == NULL && vm->last_live)
    {
        ft_printf("Le gagnant: %20s\n", vm->last_live->name);
        return (END_GAME);
    }
    /* garder une valeur de retour pour la condition d'arrêt du while de cycles() ? 
    ** ex : si plus qu'un ou moins en vie, return 0
    */
    return (0);
}