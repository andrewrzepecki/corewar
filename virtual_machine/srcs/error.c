/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:18:27 by andrewrze         #+#    #+#             */
/*   Updated: 2019/10/17 12:18:28 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int         init_error(int error, t_vm *vm)
{
    free(vm);
    ft_printf("Error code: %d\n", error);
    return (1);
}

