/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrzepec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:51:00 by anrzepec          #+#    #+#             */
/*   Updated: 2019/10/16 16:51:01 by anrzepec         ###   ########.fr       */
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
	return (0);
}

void	init_players(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->player[i].id = i + 1;
		vm->player[i].size = 0;
		i++;
	}
}

t_vm 	*init_vm(int ac)
{
	t_vm *vm;

	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		return (NULL);
	vm->process = NULL;
	vm->last_live = NULL;
	vm->dump = 0;
	vm->nb_args = ac;
	vm->nb_players = 0;
	vm->cycles = 0;
	vm->nb_lives = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->nb_checks = 0;
	init_players(vm);
	return (vm);
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
	//if ((err = load_arena(vm)))
	//	return (init_error(err, vm));
	//execute_vm(vm);
	free(vm);
	return (0);
}