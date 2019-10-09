/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/25 17:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 11:03:57 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libft.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

# define LIST_OPTION "ndvg"
# define FP ft_printf
# define CHUNK_SIZE 5000
# define CVOID ((t_process *)(proc->content))

# define VERBOSE_ONLY_ESSENCIALS 0
# define VERBOSE_SHOW_LIVES 1
# define VERBOSE_SHOW_CYCLES 2
# define VERBOSE_SHOW_OPERATIONS 4
# define VERBOSE_SHOW_DEATHS 8
# define VERBOSE_SHOW_PC_MOVEMENTS 16

/*****************************
 * definition des structures *
*****************************/

typedef struct		s_op
{
	char		*name;
	int			param_count;
	t_arg_type	param_type[3];
	int			code;
	int			cycles;
	char		*comment;
	t_bool		use_ocp;
	t_bool		dir_size;
}					t_op;

extern t_op		op_tab[17];

typedef struct			s_option
{
	char				expected_arg;
	long				dump;
	char				verbose;
	int					fd[MAX_PLAYERS];
	int					n[MAX_PLAYERS];
	int					nb_champ;
}						t_option;

typedef struct			s_data
{
	long				dump;
	char				verbose;
	unsigned long long	cycle;
	unsigned int		nb_live;
	unsigned int		nb_check;
	unsigned int		nb_process;
	int					cycle_to_die;
	char				arena[MEM_SIZE];
	int					last_player_alive;
	t_list				*pchain;
}						t_data;

typedef struct			s_process
{
	unsigned int		reg[REG_NUMBER];
	unsigned int		pc;
	int 				cycle;
	int					is_alive;
	char				id_player;
	int					carry;
	char				opc_curr;
	unsigned int		id;
	t_list				*prev;
}						t_process;

/******************************************
 * Fonction d'initialisation de structure *
******************************************/
void	init_arena_data(t_data *arena_data);
void	init_arg_data(t_option *arg_data);
t_list	*generate_process_list(t_option arg_data, char *arena); // version liste -- a voir si c est coherent
//t_process	*gen_process_tab(t_option arg_data);   // bon les listes ont l air d etre plus simples d utilisation finalement

/***********************
 * Fonction de parsing *
***********************/
# define OUVRE_UN_FICHIER 0
# define RECUPERE_OPTIONS 1
# define RECUPERE_VALEURS 2
# define INSTRUCT_CODE_ERROR -1

void	process_arg(t_option *arg_data, int ac, char **av);
void	get_value_for(char *str, t_option *arg_data);
void	get_option(char *str, t_option *arg_data);
void	get_champ(char *champ_path, t_option *arg_data);

void	process_champ(t_option *arg_data, t_header (*header)[MAX_PLAYERS], char *arena);
void	get_data_of_champ(t_header *header, const char src[]);
void	set_n_number(t_option *arg_data);

/*********************
 * Fonction d'erreur *
 * et erreurs		 *
*********************/

# define ERR_MALLOC 0
# define ERR_FILE_MAGIC 1
# define ERR_FILE_SIZE 2
# define ERR_FILE_CORRUPT 3

void	usage(void);
void	f_error(int err_nb);

/************************
 * Fonction de debugage *
 * et de test			*
************************/
void	show_struct_option(t_option arg_data);
void	show_struct_data(t_data arena_data);
void	tester_lst(t_list *elem);
void	tester_1_lst(t_list *elem);

/**********************
 * partie cycle		  *
**********************/

int		browse_lst(t_list *begin, t_data *arena_data, int verbose);
void	cycle(t_data *arena_data, t_header champs_data[], t_list *process_chain, int verbose);
long	process_move(t_list *proc, t_data *arena_data);

/***********************
 *   les instructions  *
***********************/
void	live(t_process *process, t_data *arena_data, int verbose);
void	direct_load(t_process *process, t_data *arena_data, int verbose);
void    direct_store(t_process *process, t_data *arena_data, int verbose);
void    aritmetical_addition(t_process *process, t_data *arena_data, int verbose);
void    aritmetical_substraction(t_process *process, t_data *arena_data, int verbose);
void	logical_and(t_process *process, t_data *arena_data, int verbose);
void	logical_or(t_process *process, t_data *arena_data, int verbose);
void    logical_xor(t_process *process, t_data *arena_data, int verbose);
void    jump_if_zero(t_process *process, t_data *arena_data, int verbose);
void    indirect_load(t_process *process, t_data *arena_data, int verbose);
void    indirect_store(t_process *process, t_data *arena_data, int verbose);
void    short_fork(t_process *process, t_data *arena_data, int verbose);
void    long_direct_load(t_process *process, t_data *arena_data, int verbose);
void    long_indirect_load(t_process *process, t_data *arena_data, int verbose);
void    long_fork(t_process *process, t_data *arena_data, int verbose);
void    aff(t_process *process, t_data *arena_data, int verbose);

/*********************
 * Fonction de libft *
*********************/
long	ft_atol(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *b, size_t n);
#endif
