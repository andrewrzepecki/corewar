/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:37:07 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/21 22:32:23 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

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
	{{0}, 0, {0}, 0, 0, {0}, 0, 0}
};

t_process         *load_process_from_player(t_player player)
{
    t_process *process;

    if (!(process = (t_process*)malloc(sizeof(t_process))))
        return (NULL);
    process->id = player.id;
    process->carry = 0;
    process->last_live = 0;
    process->cycles_left = op_tab[process->current_op - 1].cycles;
    process->pc = player.init_pc;
    process->current_op = player.exec[0];
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