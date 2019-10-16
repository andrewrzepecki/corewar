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

int		init_error(int error, t_vm *vm)
{
	// print error code
	//if (vm != NULL)
	//		free(vm);
	return (1);
}

int		load_arena(t_vm *vm)
{

}

int		load_players(int ac, char **av, t_vm *vm)
{
	int i;

	i = 0;
	while (i < ac)
	{
		
	}
}

int		main(int ac, char **av)
{
	int		err;
	t_vm	*vm;

	err = 0;
	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		return (1);
	if ((err = load_players(ac, av, vm)))
		return (init_error(err, vm));
	if ((err = load_arena(vm)))
		return (init_error(err, vm));
	execute_vm(vm);
	free_vm(vm);
	return (0);
}