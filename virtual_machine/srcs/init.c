/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:46:35 by andrewrze         #+#    #+#             */
/*   Updated: 2019/11/20 18:13:19 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "virtual_machine.h"

int		get_master(t_vm *vm, int master)
{
	int i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->player[i].id == -master)
			return (i);
		i++;
	}
	return (0);
}

void    create_arena(t_vm *vm)
{
    int			i;
    int			div;
	t_process	*tracer;

    i = 0;
    div = MEM_SIZE / vm->nb_players;
	tracer = vm->process;
    while (tracer)
    {
        ft_memcpy(vm->mem + (div * i), vm->player[get_master(vm, tracer->master)].exec, vm->player[get_master(vm, tracer->master)].size);
        ft_memset(vm->owner + (div * i), -vm->player[get_master(vm, tracer->master)].id, vm->player[get_master(vm, tracer->master)].size);
		vm->player[get_master(vm, tracer->master)].init_pc = div * i;
		tracer = tracer->next;
        i++;
    }
}

 void	init_players(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->player[vm->nb_players].id = -1;
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
	vm->process = (t_process*)malloc(sizeof(t_process)); // *
	vm->process = NULL; // *
	// Le russe dit qu'elle doit etre initialisé avec le plus grand id de joueur
	vm->dump = -1;
	vm->nb_args = ac;
	vm->nb_players = 0;
	vm->cycles = 0;
	vm->nb_lives = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->nb_checks = 0;
	vm->last_verif = 0; // NEW ! usefull ?
	vm->lives_since_check = 0;
	vm->nb_option = 0;
	ft_bzero(vm->player_numbers, 4);
	init_players(vm);
	return (vm);
}