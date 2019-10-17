/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrzepec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:56:35 by anrzepec          #+#    #+#             */
/*   Updated: 2019/10/16 13:56:37 by anrzepec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRUAL_MACHINE_H
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

/*
Structures basees sur le cookcook du russe/Ukrainien 
*/

typedef struct			s_player
{
	int					id;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	int					size;
	char				exec[CHAMP_MAX_SIZE + 1];
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
	t_player			player[MAX_PLAYERS];
	t_process     		*process;
	t_player			*last_live; 	/* addresse du joueur ayant appele 'live' en dernier */
	int					cycles;
	int					nb_lives;  		/* nombre de 'live' durant chaque cycle_to_die */
	int					cycles_to_die;  /* = CYCLES_TO_DIE || cycles avant ??verifications?? */
	int					nb_checks; 		/* ?? */
}						t_vm;

/*
	Parsing tools
*/
int		parse_options(t_vm *vm, char **av, int *i);
int		parse_player(t_vm *vm, char **av, int *i);

/*
Operations
*/

#endif