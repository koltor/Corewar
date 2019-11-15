/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/25 17:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 16:42:35 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

# define LIST_OPTION "ndvg"
# define FP ft_printf
# define U unsigned
# define UINT unsigned int
# define CHUNK_SIZE 5000

# define VERBOSE_ONLY_ESSENCIALS 0
# define VERBOSE_SHOW_LIVES 1
# define VERBOSE_SHOW_CYCLES 2
# define VERBOSE_SHOW_OPERATIONS 4
# define VERBOSE_SHOW_DEATHS 8
# define VERBOSE_SHOW_PC_MOVEMENTS 16

/*
** definition des structures
*/

typedef struct	s_op
{
	char		*name;
	int			param_count;
	t_arg_type	param_type[3];
	int			code;
	int			cycles;
	char		*comment;
	t_bool		use_ocp;
	t_bool		dir_size;
}				t_op;

extern t_op		g_op_tab[17];

typedef struct	s_option
{
	char			expected_arg;
	long			dump;
	char			verbose;
	int				fd[MAX_PLAYERS];
	unsigned int	n[MAX_PLAYERS];
	int				nb_champ;
	t_bool			visu;
}				t_option;

typedef struct	s_data
{
	long			dump;
	char			verbose;
	t_bool			visu;
	long			cycle;
	unsigned int	nb_live;
	unsigned int	nb_check;
	unsigned int	living_process;
	unsigned int	ids_process;
	int				cycle_to_die;
	char			arena[MEM_SIZE];
	int				last_player_alive;
	int				nb_champ;
	unsigned int	n[MAX_PLAYERS];
	t_header		champs_data[MAX_PLAYERS];
	t_list			*pchain;
}				t_data;

typedef struct	s_process
{
	unsigned int	id;
	char			id_player;
	int				is_alive;
	unsigned int	last_live;
	int				carry;
	unsigned int	reg[REG_NUMBER];
	unsigned int	pc;
	unsigned char	opc_curr;
	unsigned char	ocp_curr;
	int				cycle;
	char			op_shape[11];
	unsigned char	curr_op_size;
	unsigned int	size_params[3];
	int				param[3];
	int				param_value[3];
	t_bool			valid_ocp;
	t_bool			to_move;
	t_bool			valid_op;
}				t_process;

/*
** Fonction d'initialisation de structure et de liste
*/

void			generate_process_list(t_data *data, int i);

/*
**				 Fonction de parsing
*/

# define OUVRE_UN_FICHIER 0
# define RECUPERE_OPTIONS 1
# define RECUPERE_VALEURS 2
# define INSTRUCT_CODE_ERROR -1

void			process_arg(t_option *arg_data, int ac, char **av);
void			get_value_for(char *str, t_option *arg_data);
void			get_option(char *str, t_option *arg_data);
void			get_champ(char *champ_path, t_option *arg_data);
void			process_champ(t_option *arg_data,
							t_header (*header)[MAX_PLAYERS], char *arena);
void			get_data_of_champ(t_header *header, const char src[]);
void			set_n_number(t_option *arg_data);

/*
**		Fonction d'erreur
*/

# define ERR_MALLOC 0
# define ERR_FILE_MAGIC 1
# define ERR_FILE_SIZE 2
# define ERR_FILE_CORRUPT 3

void			usage(void);
void			f_error(int err_nb);

/*
** partie analyse
*/

char			fill_params_tab(unsigned char ocp, int value);
void			read_ocp(t_process *proc);
char			get_param_type(char ocp, char params);
int				print_spaces(unsigned int nb, unsigned int nb_process);
void			transfer_on_ram(t_data *data, t_process *proc, int id,
																	int pos);
void			transfer_in_proc(t_data *data, t_process *proc, int id,
																int pos);

/*
** partie cycle
*/

void			cycle(t_data *data);
void			browse_process(t_data *data);
void			process_move(t_process *proc, t_data *data, int verbose);
void			affect_new_ocp(t_process *proc, t_data *data);
void			affect_new_opc(t_process *proc, t_data *data);

/*
** partie de liberation
*/

void			clean_list(t_list *begin);
void			kill_dead_process(t_data *data);

/*
** les instructions
*/

void			live(t_process *process, t_data *data, int verbose);
void			direct_load(t_process *process, t_data *data,
														int verbose);
void			direct_store(t_process *process, t_data *data,
														int verbose);
void			aritmetical_addition(t_process *process, t_data *data,
														int verbose);
void			aritmetical_substraction(t_process *process, t_data *data,
														int verbose);
void			logical_and(t_process *process, t_data *data,
														int verbose);
void			logical_or(t_process *process, t_data *data,
														int verbose);
void			logical_xor(t_process *process, t_data *data,
														int verbose);
void			jump_if_zero(t_process *process, t_data *data,
														int verbose);
void			indirect_load(t_process *process, t_data *data,
														int verbose);
void			indirect_store(t_process *process, t_data *data,
														int verbose);

void			short_fork(t_process *process, t_data *data, int verbose);
void			long_fork(t_process *process, t_data *data, int verbose);
t_list			*copy_process(t_data *data, t_process *proc, int bv);
void			check_landing(t_process *fork, t_data *data);

void			long_direct_load(t_process *process, t_data *data,
															int verbose);
void			long_indirect_load(t_process *process, t_data *data,
															int verbose);
void			aff(t_process *process, t_data *data, int verbose);

/*
** AUTRES
*/

t_bool			op_has_ocp(int opc);
char			get_param_type(char ocp, char param);
void			get_params(t_data *data, t_process *proc);
t_bool			compute_params(t_data *data, t_process *proc);
void			*ft_memcpy_memsize(void *dst, const void *src, int idx,
																size_t n);
void			print_memory(const void *addr, size_t size, int base);
void			print_memory_memsize(const void *addr, size_t size, int start);
void			print_memory_hexa(const void *addr, size_t size);
void			print_space_for_indirect(int nb);

/*
** les funcs visualizer
*/

t_bool			init_sdl();
void			init_foot_print(t_data *data);
void			print_footprint(int idx, int len, int n);
void			set_live_visu_bzero();
void			set_live_visu(char id);
t_bool			loop_corewar(t_data *data, unsigned long cycle_local);
void			show_the_winner(t_data *data, unsigned long cycle_local);
void			quit_sdl();

void			play_sound(char opc);
#endif
