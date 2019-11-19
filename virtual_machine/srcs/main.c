/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:51:00 by anrzepec          #+#    #+#             */
/*   Updated: 2019/10/22 19:02:39 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int		load_players(char **av, t_vm *vm)
{
	int i;
	int	err;

	i = 0;
	while (++i < vm->nb_args)
	{
		if (av[i] && av[i][0] == '-')
		{
			if (parse_option(vm, av, &i))
				return (OPTION_ERROR);
		}
		else if ((err = parse_player(vm, av, i)))
			return (err);
	}
	// i = 0;
	// while (i < vm->nb_players)
	// {
	// 	ft_printf("%s: %d\n", vm->player[i].name, vm->player[i].id);
	// 	i++;
	// }
	return (vm->nb_players > 1 ? 0 : 1);
}

int		main(int ac, char **av)
{
	int		err;
	t_vm	*vm;

	err = 0;
	if (!(vm = init_vm(ac)))
		return (1);
	if ((err = load_players(av, vm)))
		return (init_error(err, vm));
	create_arena(vm);
	load_process_list(vm);
	vm->last_live = &vm->player[vm->nb_players];
	if (exec_machine(vm) == ALLOC_ERROR)
		return (init_error(ALLOC_ERROR, vm));
	free(vm);
	return (0);
}