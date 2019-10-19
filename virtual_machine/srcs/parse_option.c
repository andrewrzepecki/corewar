/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:15:46 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/17 16:56:01 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/* 
** ON GOING:    check MAX_INT for player number.
**              deal with clashing player numbers.
*/

int     visualizer_option(t_vm *vm, char **av, int *i)
{
    if ((*i + 1) < vm->nb_args && ft_strnum(av[*i + 1]))
    {
            vm->vis = ft_atoi(av[++(*i)]);
            if (vm->vis > 0)
                return (OH_OUI);
    }
    return (VIS_ERROR);
}

int     check_player_numbers(t_vm *vm, int player_nb)
{
    int     i;

    i = 0;
    while (i < vm->nb_players)
    {
        if (vm->player[player_nb].id == vm->player[i].id && i != player_nb)
        {
            vm->player[i].id++;
            return (check_player_numbers(vm, i));
        }
        i++;
    }
    return (0);
}

int     number_option(t_vm *vm, char **av, int *i)
{
    if ((*i + 1) < vm->nb_args && ft_strnum(av[*i + 1]))
    {
        if (vm->nb_players < MAX_PLAYERS)
        {
            if ((vm->player[vm->nb_players].id = ft_atoi(av[++(*i)])) > 0)
                return (check_player_numbers(vm, vm->nb_players));
        }
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
    if (!ft_strcmp(av[*i], "-v"))
        return (visualizer_option(vm, av, i));
    if (!ft_strcmp(av[*i], "-n"))
        return (number_option(vm, av, i));
    if (!ft_strcmp(av[*i], "-dump"))
        return (dump_option(vm, av, i));
    return (1);
}