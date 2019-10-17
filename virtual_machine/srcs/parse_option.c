/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:15:46 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/16 21:15:50 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/* 
** ON GOING:    check MAX_INT for player number.
                deal with clashing player numbers.
*/
int     number_option(t_vm *vm, char **av, int *i)
{
    if ((*i + 1) < vm->nb_args && ft_strnum(av[*i + 1]))
    {
        if (vm->nb_players < MAX_PLAYERS)
            vm->player[vm->nb_players].id = ft_atoi(av[++(*i)]);
        return (OH_OUI);
    }
    return (PLAYER_NUMBER_ERROR);
}

int     dump_option(t_vm *vm, char **av, int *i)
{
    if ((*i + 1) < vm->nb_args && ft_strnum(av[*i + 1]))
    {
        vm->dump = ft_atoi(av[++(*i)]);
        return (OH_OUI);
    }
    return (DUMP_ERROR);
}

int     parse_option(t_vm *vm, char **av, int *i)
{
    if (!ft_strcmp(av[*i], "-n"))
        return (number_option(vm, av, i));
    if (!ft_strcmp(av[*i], "-dump"))
        return (dump_option(vm, av, i));
    return (1);
}

