/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vegeta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:43:37 by eviana            #+#    #+#             */
/*   Updated: 2019/11/14 16:52:21 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define IDX_MOD 512
#define MEM_SIZE (4 * 1024)

int vegetable_garden(int pc, int addr)
{
	int restr_addr;
	int	new_addr;

	restr_addr = addr % IDX_MOD;
	printf("restr_addr = %d\n", restr_addr);
	if (restr_addr > IDX_MOD / 2)
		restr_addr = - IDX_MOD + restr_addr;
	new_addr = pc + restr_addr;
	if (new_addr < 0)
		new_addr = MEM_SIZE + new_addr;
	printf("new_addr = %d\n", new_addr);
	return (new_addr);
}

int main(int argc, char **argv)
{
    printf("Vegeta dit : %d\n", vegetable_garden(atoi(argv[1]), atoi(argv[2])));
    (void)argc;
}