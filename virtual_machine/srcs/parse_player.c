/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:56:27 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/16 22:56:31 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int     parse_magic(int fd)
{
    char    buff[4];
    int     bytes;
    long long  res;

    if (read(fd, &buff, 4) < 4)
        return (1);
    bytes = 0;
    res = 0;
    while (bytes < 4)
    {
        res += buff[bytes] * ft_power(256, (4 - (bytes + 1)));
        ft_printf("byte = %d -> res = %lld\n", buff[bytes], res);
        bytes++;
    }
    if (res == COREWAR_EXEC_MAGIC)
        return (0);
    ft_printf("magic: %lld \n", res);
    return (1);
}

int     parse_exec(int fd, t_vm *vm)
{
    char    buff[CHAMP_MAX_SIZE + 1];
    int     bytes;

    if (read(fd, buff, 4) != 4)
        return (1);
    bytes = 4;
    while (bytes)
    {
        vm->player[vm->nb_players].size += buff[bytes - 1] * ft_power(256, (4 - bytes));
        bytes--;
    }
    if (vm->player[vm->nb_players].size < CHAMP_MAX_SIZE)
        if (read(fd, buff, vm->player[vm->nb_players].size)
            == vm->player[vm->nb_players].size)
            return (0);
    return (1);
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
    if (read(fd, vm->player[vm->nb_players].name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
        return (NAME_ERROR);
    if (read(fd, vm->player[vm->nb_players].comment, COMMENT_LENGTH) != COMMENT_LENGTH)
        return (COMMENT_ERROR);
    if (parse_exec(fd, vm))
        return (EXEC_ERROR);
    vm->nb_players++;
    return (OH_OUI);
}

