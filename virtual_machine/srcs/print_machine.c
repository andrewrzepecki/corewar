/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:27:25 by eviana            #+#    #+#             */
/*   Updated: 2019/11/20 20:39:56 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void    print_bytes(t_vm *vm, int i)
{
    int color;
    
    color = vm->owner[i] % 8;
    if (color == 0)
        ft_printf("{eoc}%02x ", vm->mem[i]); // & 0xFF); pour switch char
    else if (color == 1)
        ft_printf("{red}%02x ", vm->mem[i]); // & 0xFF);
    else if (color == 2)
        ft_printf("{green}%02x ", vm->mem[i]); // & 0xFF);
    else if (color == 3)
        ft_printf("{purple}%02x ", vm->mem[i]); // & 0xFF);
    else if (color == 4)
        ft_printf("{blue}%02x ", vm->mem[i]); // & 0xFF);
    else if (color == 5)
        ft_printf("{yellow}%02x ", vm->mem[i]); // & 0xFF);
    else if (color == 6)
        ft_printf("{cyan}%02x ", vm->mem[i]); // & 0xFF);
    else if (color == 7)
        ft_printf("{magenta}%02x ", vm->mem[i]); // & 0xFF);
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

void    print_regs(t_vm *vm, int line)
{
    int i;
    t_process *proc;

    proc = vm->process;
    while (proc->id != 1)
        proc = proc->next;
    if (line == 17)
    {
        i = 1;
        pannel_line("Proc regs : ");
        while (i < 9)
        {
            ft_printf("[%d]", proc->reg[i]);
            i++;
        }
        ft_printf("\n");
    }
    else if (line == 18)
    {
        i = 9;
        pannel_line("Proc regs : ");
        while (i < 17)
        {
            ft_printf("[%d]", proc->reg[i]);
            i++;
        }
        ft_printf("\n");
    }
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
        //ft_printf("%s (%d)", vm->last_live->name, vm->last_live->id); // BESOIN IMPLEMENTATION AVANT
    }
    else if (line == 13)
    {
        pannel_line("cycles to die : ");
        ft_printf("%d", vm->cycles_to_die); 
    }
    else if (line == 9 || line == 15)
        ft_printf("-----------------------------------------------------------------");
    ft_printf("\n");
    //print_regs(vm, line);
}

void    debug_lines(t_vm *vm)
{
    int         i;
    t_process   *current;

    current = vm->process;
    ft_printf("\nDEBUG :\n");
    while (current)
    {
        i = 0;
        ft_printf("Proc %d(m%d) pc : %d | c_op : %d | c_left : %d | last_l : %d | regs : [", current->id, current->master, current->pc, current->current_op, current->cycles_left, current->last_live);
        while (++i < 17)
            ft_printf("%d : %d | ", i, current->reg[i]);
        ft_printf("]\n");
        current = current->next;
    }
}

void    print_col_numbers(void)
{
    int i;

    i = 0;
    ft_printf("Col nb : ");
    while (i < 64) // A VIRER, PRINT LA PREMIERE LIGNE NUMEROTE
    {
        ft_printf("%02d ", i);
        i++;
    }
    ft_printf("     |\n");
}

int     print_arena(t_vm *vm)
{
    int             i;
    int             lines;

    i = 0;
    ft_printf("\e[1;1H\e[2J"); // Pour clear le board
    //ft_printf("\033[2J\033[1;1H");
    print_col_numbers();
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
    //debug_lines(vm);
    return (0);
}

int     print_dump(t_vm *vm)
{
    int             i;
    int             lines;

    i = 0;
    //ft_printf("\e[1;1H\e[2J"); // Pour clear le board
    lines = ft_sqrt(MEM_SIZE);
    while (i < MEM_SIZE)
    {
        if (i != 0 && i % lines == 0)
            ft_printf("\n");
        if (i % lines == 0)
            ft_printf("0x%04x : ", i);
        ft_printf("%02x ", vm->mem[i]);
        i++;
    }
    ft_printf("\n");
    //debug_lines(vm);
    return (0);
}