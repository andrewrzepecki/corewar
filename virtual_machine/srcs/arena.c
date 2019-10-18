/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:27:25 by eviana            #+#    #+#             */
/*   Updated: 2019/10/18 18:03:40 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void    print_bytes(t_vm *vm, int i)
{
    int color;
    
    color = vm->owner[i] % 8;
    if (color == 0)
        ft_printf("{eoc}%02x ", vm->mem[i]);
    else if (color == 1)
        ft_printf("{red}%02x ", vm->mem[i]);
    else if (color == 2)
        ft_printf("{green}%02x ", vm->mem[i]);
    else if (color == 3)
        ft_printf("{purple}%02x ", vm->mem[i]);
    else if (color == 4)
        ft_printf("{blue}%02x ", vm->mem[i]);
    else if (color == 5)
        ft_printf("{yellow}%02x ", vm->mem[i]);
    else if (color == 6)
        ft_printf("{cyan}%02x ", vm->mem[i]);
    else if (color == 7)
        ft_printf("{magenta}%02x ", vm->mem[i]);
}

void    pannel_line(char *line)
{
    char    pannel[60];

    ft_bzero(pannel, 60);
    ft_printf(ft_strcat(ft_strcpy(pannel, "          "), line));
}

void    print_war(int line)
{
    if (line == 2)
        ft_printf("                   />");
    else if (line == 3)
        ft_printf("      ()          //---------------------------(");
    else if (line == 4)
        ft_printf("     (*)OXOXOXOXO(*>        --COREWAR--         {red}\\{eoc}");
    else if (line == 5)
        ft_printf("      ()          \\\\-----------{red}------------------){eoc}");
    else if (line == 6)
        ft_printf("                   \\>                          {red}  \"{eoc}");
    else if (line == 7)
        ft_printf("                                                 {red}'{eoc}");
}

void    print_pannel(t_vm *vm, int line)
{
    ft_printf("{eoc}     |");
    if (line < 8)
        print_war(line);
    else if (line == 11)
    {
        pannel_line("current cycle : ");
        ft_printf("%d", vm->cycles);
    }
    else if (line == 12)
    {
        pannel_line("last alive : ");
        ft_printf("%s", vm->player[0].name);
    }
    else if (line == 13)
    {
        pannel_line("cycles to die : ");
        ft_printf("%d", vm->cycles_to_die); 
    }
    else if (line == 9 || line == 15)
        ft_printf("-----------------------------------------------------------------");
    ft_printf("\n");
}

int     print_arena(t_vm *vm)
{
    int             i;
    int             lines;

    i = 0;
    ft_printf("\e[1;1H\e[2J");
    //ft_printf("\033[2J\033[1;1H");
    lines = ft_sqrt(MEM_SIZE);
    while (i < MEM_SIZE)
    {
        if (i != 0 && i % lines == 0)
            print_pannel(vm, i / lines);
        if (i % lines == 0)
            ft_printf("0x%04x : ", i);
        print_bytes(vm, i);
        i++;
    }
    ft_printf("{eoc}     |\n");
    return (0);
}

void    create_arena(t_vm *vm)
{
    int     i;
    int     div;

    i = 0;
    div = MEM_SIZE / vm->nb_players;
    while (i < vm->nb_players)
    {
        ft_memcpy(vm->mem + (div * i), vm->player[i].exec, vm->player[i].size);
        ft_memset(vm->owner + (div * i), vm->player[i].id, vm->player[i].size);
        i++;
    }
}