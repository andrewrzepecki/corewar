/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:37:07 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/22 14:39:48 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_process         *load_process_from_player(t_player player)
{
    t_process *process;

    if (!(process = (t_process*)malloc(sizeof(t_process))))
        return (NULL);
    process->id = player.id;
    process->carry = 0;
    process->last_live = 0;
    process->current_op = player.exec[0];
    process->cycles_left = g_op_tab[process->current_op - 1].cycles;
    process->pc = player.init_pc;
    //process->next_op = get_next_op(process->id); // Je pense que ce n'est pas utile a ce stade
    process->reg[0] = process->id; // a verifier si mettre celui du joueur ou du process
    process->next = NULL;
    ft_bzero(process->reg + 4, (REG_NUMBER - 1) * 4);
    return (process);
}

void        place_process(t_process **lst, t_process *proc)
{
    t_process *tmp;
    t_process *tracer;

    tracer = *lst;
    if (!*lst)
        *lst = proc;
    else
    {
        while (tracer->next && tracer->next->id > proc->id)
            tracer = tracer->next;
        tmp = tracer->next;
        tracer->next = proc;
        proc->next = tmp;
    }
}

int        load_process_list(t_vm *vm)
{
    int i;
    t_process *proc;

    i = 0;
    while (i < vm->nb_players)
    {
        if (!(proc = load_process_from_player(vm->player[i])))
            return (ALLOC_ERROR);
        place_process(&(vm->process), proc);
        i++;
    }
    return (0);
}