/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:56:35 by anrzepec          #+#    #+#             */
/*   Updated: 2019/11/01 20:25:54 by eviana           ###   ########.fr       */
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
# define ALLOC_ERROR			12
# define VIS_ERROR				13

/* 
** COLORS
*/

# define RED					"{red}"

typedef struct 			s_op
{
	char 				name[6];
	int					params;
	int					type[3];
	int					op_number;
	int					cycles;
	char				description[50];
	int					ocp;
	int					dir_size;
	int					restr;
}						t_op;

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
	int					init_pc;
	int					last_live;		/* cycle du dernier live */
}						t_player;

typedef struct 			s_process
{
	int					id;
	int					carry;  
	int					current_op; 	/* operation a executer */
	int					last_live;		/* cycle du dernier 'live' */
	int					cycles_left; 	/* cycles restant avant execution */
	int					pc;				/* position sur l'arene du cariage */
	int					next_op; 		/* utile ? nombre d'octets avant prochaine operation */
	int					reg[REG_NUMBER];/* registres du carriage ??? unique au carriage ou commum pour chaque process */
	struct s_process	*next;
}						t_process;

/* 
	Apres initialisation de la vm, avec les joueurs et le code executable, a chaque cycle, lire chaque carriage dans l'ordre,
	et executer selon les variables propre a chque cycle. 
*/

// typedef struct 			s_mem
// {
// 	unsigned char		x;
// 	unsigned char		owner;
// }						t_mem;

typedef	struct			s_vm
{
	int					dump;
	int					vis;
	int					nb_args;
	int					nb_players;
	unsigned char		mem[MEM_SIZE];
	unsigned char		owner[MEM_SIZE];
	t_player			player[MAX_PLAYERS];
	t_process     		*process;		// anciennement **process
	t_player			*last_live; 	/* addresse du joueur ayant appele 'live' en dernier */
	int					cycles;
	int					nb_lives;  		/* nombre de 'live' durant chaque cycle_to_die */
	int					cycles_to_die;  /* = CYCLES_TO_DIE || cycles avant ??verifications?? */
	int					nb_checks; 		/* ?? */
	int					last_verif;		/* cycle de la dernière verification des process en vie */
	int					nb_proc;
}						t_vm;

typedef struct    s_param
{
  int n[3];		// La valeur du parametre
  int c[3];		// Le code / type du parametre : REG, IND, DIR ?
  int valid;	// Pour remonter un probleme de validité des paramétres
}                 t_param;

extern t_op				g_op_tab[17];

/*
**	Init
*/
t_vm	*init_vm(int ac);
void	init_players(t_vm *vm);
void	create_arena(t_vm *vm);
int 	load_process_list(t_vm *vm);

/*
** Parsing
*/
int		parse_option(t_vm *vm, char **av, int *i);
int		parse_player(t_vm *vm, char **av, int i);
int     check_player_numbers(t_vm *vm, int player_nb);

/*
** Runtime
*/
void	cycles(t_vm *vm);
t_param	set_params(t_vm *vm, t_process *proc, int pc, int *offset);

/*
** Operations
*/
int		op_live(t_vm *vm, t_process *proc);
int		op_ld(t_vm *vm, t_process *proc);
int		op_st(t_vm *vm, t_process *proc);
int		op_add(t_vm *vm, t_process *proc);
int		op_sub(t_vm *vm, t_process *proc);
int		op_and(t_vm *vm, t_process *proc);
int		op_or(t_vm *vm, t_process *proc);
int		op_xor(t_vm *vm, t_process *proc);
int		op_zjmp(t_vm *vm, t_process *proc);
int		op_ldi(t_vm *vm, t_process *proc);
int		op_sti(t_vm *vm, t_process *proc);
int		op_fork(t_vm *vm, t_process *proc);
int		op_lld(t_vm *vm, t_process *proc);
int		op_lldi(t_vm *vm, t_process *proc);

/*
** Tools
*/
int		is_valid_op(int opcode);
int		is_valid_reg(int reg);
void    init_registers(t_process *process);
void    copy_registers(t_process *new, t_process *proc);
int		rel_address(t_process *proc, int add1, int add2);
int		long_rel_address(t_process *proc, int add1, int add2);
int		read_address(t_vm *vm, int addr, size_t bytes);
int		read_bytes(unsigned char *mem, size_t size);
void	write_to_address(t_vm *vm, t_process *proc, int addr, int to_write);

/*
** Error management
*/
int		init_error(int error, t_vm *vm);

/*
** Print
*/
int		print_arena(t_vm *vm);

/*
** Tests
*/

#endif