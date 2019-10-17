/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:56:35 by anrzepec          #+#    #+#             */
/*   Updated: 2019/10/17 17:12:51 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

# include "libft.h"
# include "op.h"

/* 
** ERROR CODES
*/

# define OH_OUI					0
# define OPTION_ERROR 			1
# define PLAYER_NUMBER_ERROR 	2
# define DUMP_ERROR				3
# define FILE_ERROR				4
# define PLAYER_OVERLOAD		5
# define NAME_ERROR				7
# define COMMENT_ERROR			8
# define EXEC_ERROR				9
# define MAGIC_ERROR			10
# define SIZE_ERROR				11

/*
Structures basees sur le cookcook du russe/Ukrainien 
*/

typedef struct			s_player
{
	int					id;
	char				name[PROG_NAME_LENGTH + 4];
	char				comment[COMMENT_LENGTH + 4];
	unsigned int		size;
	char				exec[CHAMP_MAX_SIZE];
}						t_player;

typedef struct 			s_process
{
	int					id;
	int					carry;  
	int					current_op; 	/* operation a executer */
	int					last_live;		/* cycle du dernier 'live' */
	int					cycles_left; 	/* cycles restant avant execution */
	int					pc;   	/* position sur l'arene du cariage */
	int					next_op; 			/* nombre d'octets avant prochaine operation */
	int					reg[REG_NUMBER];/* registres du carriage ??? unique au carriage ou commum pour chaque process */
	struct s_process	*next;
}						t_process;

/* 
	Apres initialisation de la vm, avec les joueurs et le code executable, a chaque cycle, lire chaque carriage dans l'ordre,
	et executer selon les variables propre a chque cycle. 
*/

typedef	struct			s_vm
{
	int					dump;
	int					nb_args;
	int					nb_players;
	unsigned char		mem[MEM_SIZE];
	t_player			player[MAX_PLAYERS];
	t_process     		*process;
	t_player			*last_live; 	/* addresse du joueur ayant appele 'live' en dernier */
	int					cycles;
	int					nb_lives;  		/* nombre de 'live' durant chaque cycle_to_die */
	int					cycles_to_die;  /* = CYCLES_TO_DIE || cycles avant ??verifications?? */
	int					nb_checks; 		/* ?? */
}						t_vm;

/*
** Parsing tools
*/

int		parse_option(t_vm *vm, char **av, int *i);
int		parse_player(t_vm *vm, char **av, int i);
int		read_bytes(unsigned char *mem, size_t size);

/*
**	Init
*/

void	create_arena(t_vm *vm);

/*
** Error management
*/

int		init_error(int error, t_vm *vm);

/*
** Operations
*/



#endif