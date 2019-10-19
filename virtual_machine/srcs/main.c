/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:51:00 by anrzepec          #+#    #+#             */
/*   Updated: 2019/10/18 18:00:49 by eviana           ###   ########.fr       */
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
	return (vm->nb_players > 1 ? 0 : 1);
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
	ft_bzero(vm->mem, MEM_SIZE);
	ft_bzero(vm->owner, MEM_SIZE);
	vm->vis = -1;
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

int			read_bytes(unsigned char *mem, size_t size)
{
	size_t bytes;
	int res;

	bytes = 0;
	res = 0;
	while (bytes < size)
	{
		res += mem[bytes] * ft_power(256, (4 - (bytes + 1)));
		bytes++;
	}
	return (res);
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

	cycles_test(vm);
	//print_arena(vm); // et si retour erreur ?
	
	//write(1, vm->mem, MEM_SIZE);
	//if ((err = load_arena(vm)))
	//	return (init_error(err, vm));
	//execute_vm(vm);
	//ft_printf("%s || %s\n", vm->player[0].name, vm->player[0].comment);
	//write(1, vm->player[0].exec, vm->player[0].size);
	free(vm);
	return (0);
}