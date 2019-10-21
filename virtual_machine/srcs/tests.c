/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:58:15 by eviana            #+#    #+#             */
/*   Updated: 2019/10/21 18:14:57 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void    cycles_test(t_vm *vm)
{
    while (1) // until players left
    {
        vm->cycles++;
        if (vm->vis > 0 && vm->vis % vm->cycles)
        {
            print_arena(vm);
            sleep(1);
        }
    }
}