/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:27:25 by eviana            #+#    #+#             */
/*   Updated: 2019/10/17 17:16:37 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void    create_arena(t_vm *vm)
{
    int i;
    int div;

    i = 0;
    div = MEM_SIZE / vm->nb_players;
    while (i < vm->nb_players)
    {
        ft_memcpy(vm->mem + (div * i), vm->player[i].exec, vm->player[i].size);
        i++;
    }
}