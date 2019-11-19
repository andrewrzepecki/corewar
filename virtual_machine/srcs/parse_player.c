/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:56:27 by andrewrze         #+#    #+#             */
/*   Updated: 2019/11/01 19:14:59 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int     parse_magic(int fd)
{
    unsigned char       buff[4];

    if (read(fd, &buff, 4) < 4)
        return (1);
    if (read_bytes(buff, 4) == COREWAR_EXEC_MAGIC)
        return (0);
    return (1);
}

int     parse_exec(int fd, t_vm *vm)
{
    unsigned char   buff[4];

    if (read(fd, buff, 4) != 4)
        return (1);
    if ((vm->player[vm->nb_players].size = read_bytes(buff, 4)) <= 0 && vm->player[vm->nb_players].size > CHAMP_MAX_SIZE)
        return (SIZE_ERROR);
    if (read(fd, vm->player[vm->nb_players].comment, COMMENT_LENGTH + 4) != COMMENT_LENGTH + 4)
        return (COMMENT_ERROR);
    if (read(fd, vm->player[vm->nb_players].exec, vm->player[vm->nb_players].size) != vm->player[vm->nb_players].size)
        return (SIZE_ERROR);
    return (0);
}

int     check_player_numbers(t_vm *vm, int player_nb)
{
    int     i;

    i = 0;
    while (i < vm->nb_players)
    {
        if (vm->player[player_nb - 1].id == vm->player[i].id && player_nb - 1 != i)
        {
            vm->player[i].id++;
            return (check_player_numbers(vm, i));
        }
        i++;
    }
    return (0);
}

int     parse_player(t_vm *vm, char **av, int i)
{
    int fd;

    if ((fd = open(av[i], O_RDONLY)) <= 0)
        return (FILE_ERROR);
    if (vm->nb_players >= MAX_PLAYERS)
        return (PLAYER_OVERLOAD);
    if (parse_magic(fd))
        return (MAGIC_ERROR);
    if (read(fd, vm->player[vm->nb_players].name, PROG_NAME_LENGTH + 4) != PROG_NAME_LENGTH + 4)
        return (NAME_ERROR);
    if (parse_exec(fd, vm))
        return (EXEC_ERROR);
    vm->nb_players++;
    vm->player[vm->nb_players - 1].id = vm->nb_option ? vm->nb_option : -vm->nb_players;
    vm->nb_option = 0;
    return (check_player_numbers(vm, vm->nb_players));
}