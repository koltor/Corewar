/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/25 17:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:45:09 by matheme     ###    #+. /#+    ###.fr     */
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

typedef	enum		e_bool
{
	true = 1,
	false = 0
}					t_bool;

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

extern t_op		g_op_tab[17];

typedef struct			s_option
{
	char				expected_arg;				// indique l'argument prochainenment attendu
	long				dump;						// indique la valeur de la verbose recuperer
	char				verbose;					//indique la valeur de la verbose recuperer
	int					fd[MAX_PLAYERS];			// contient le file descriptor de chaque champion charger
	unsigned int		n[MAX_PLAYERS];				// indique les numeros de chaque champion
	int					nb_champ;					//indique le nombre de champion charger dans l'arene
}						t_option;

typedef struct			s_data
{
	long				dump;						// le tour ou on devra dump la memoire
	char				verbose;					// la valeur de la verbose entre 0 et 31 inclus
	unsigned long long	cycle;						// le compteur de cycle Generale
	unsigned int		nb_live;					// indique le nombre de live executer pendant 1 cycle_to_die
	unsigned int		nb_check;					// nombre de cycle_to_die passé sans descendre ça valeur
	unsigned int		living_process;				// indique le nombre de process en vie
	unsigned int		ids_process;				// indique le nombre de process au'il y a eu depuis le debut de la partie
	int					cycle_to_die;				// el famouso cycle to die
	char				arena[MEM_SIZE];			// l'arene de jeux
	int					last_player_alive;			// contient l'id du player dans le tableau n
	int					nb_champ;					//indique le nombre de champion charger dans l'arene
	unsigned int		n[MAX_PLAYERS];				// met en relation un player et sa valeur -n et sa position dans les infos champions
	t_header			champs_data[MAX_PLAYERS];	// structure qui contient toute les valeurs d'un champion
	t_list				*pchain;					// indique le debut de la chaine des process
}						t_data;

typedef struct			s_process
{
	unsigned int		id;						// indique l'id du process
	char				id_player;				// contient l'id du player qui à lancer le process
	int					is_alive;				// indique si le process à effectuer un live pendant le cycle_to_die
	int					carry;					// un valeur ramdom appeler carry (elle affecque le comportement du zjmp)
	unsigned int		reg[REG_NUMBER];		// les 16 registres
	unsigned int		pc;						// indique la postion du process dans l'arene
	unsigned char		opc_curr;				// indique la valeur de la case ou se situe le process
	int 				cycle;					// indique le nombre de cycle à attendre avant la prochaine instructions

	unsigned char		curr_op_size;			// ???
	unsigned int		size_params[3];			// ???
	t_bool				to_move;				// ???
	t_bool				valid_ocp;				// ???
}						t_process;

/******************************************************
 * Fonction d'initialisation de structure et de liste *
*******************************************************/
t_list		*generate_process_list(t_data *arena_data, int i); //genere les premiers process

/******************************************************
 *				 Fonction de parsing				  *
*******************************************************/
# define OUVRE_UN_FICHIER 0
# define RECUPERE_OPTIONS 1
# define RECUPERE_VALEURS 2
# define INSTRUCT_CODE_ERROR -1

void	process_arg(t_option *arg_data, int ac, char **av); // P: recupere les infos des argument
void	get_value_for(char *str, t_option *arg_data);		// S: interprete un argument comme etant une valeur
void	get_option(char *str, t_option *arg_data);			// S: interprete un argument comme etant une option
void	get_champ(char *champ_path, t_option *arg_data);	// S: interprete un argument comme etant un champion

void	process_champ(t_option *arg_data, t_header (*header)[MAX_PLAYERS], char *arena); // P: verifie les infos de chaque champion charger
void	get_data_of_champ(t_header *header, const char src[]);							 // S: recupere les infos de header de chque champion
void	set_n_number(t_option *arg_data);												 // S: affecte un numero à chaque champion

/****************************
 *		Fonction d'erreur   *
 *		  et erreurs		*
*****************************/

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
void	show_struct_option(t_option arg_data);	// permet de regarder l'etat de la structure option
void	show_struct_data(t_data arena_data);	// permet de regarder l'etat de la structure data
void	tester_lst(t_list *elem);				// permet de regarder l'etat d'un maillon de la liste des process
void	tester_1_lst(t_list *elem);				// permet de regarder l'etat de la liste des process
void	print_params_size(t_process *proc, unsigned char ocp); // ???

/**********************
 * partie analyse	  *
**********************/
void	read_ocp(t_process *proc, t_data *arena_data);
char	fill_params_tab(unsigned char ocp, int value);
void	convert_params(int p[], t_process *proc);
void	get_op_size(t_process *proc, t_data *arena_data);

/**********************
 * partie cycle		  *
**********************/
void	cycle(t_data *arena_data);										//P: fonction de bouclage de COREWAR (en cycle par cycle)
void	browse_process(t_data *arena_data);								//S: execute la liste de process (appeler 1 fois par cycle)
int		process_move(t_process *proc, t_data *arena_data, int verbose);	//S: fonction de deplacement pour un process à la fois

/************************
 * partie de liberation *
*************************/
void	clean_list(t_list *begin);
void	kill_dead_process(t_data *arena_data);

/***********************
 *   les instructions  *
***********************/
void	live(t_process *process, t_data *arena_data, int verbose);						// live
void	direct_load(t_process *process, t_data *arena_data, int verbose);				// ld
void    direct_store(t_process *process, t_data *arena_data, int verbose);				// st
void    aritmetical_addition(t_process *process, t_data *arena_data, int verbose);		// add
void    aritmetical_substraction(t_process *process, t_data *arena_data, int verbose);	// sub
void	logical_and(t_process *process, t_data *arena_data, int verbose);				// and
void	logical_or(t_process *process, t_data *arena_data, int verbose);				// or
void    logical_xor(t_process *process, t_data *arena_data, int verbose);				// xor
void    jump_if_zero(t_process *process, t_data *arena_data, int verbose);				// zjmp
void    indirect_load(t_process *process, t_data *arena_data, int verbose);				// ldi
void    indirect_store(t_process *process, t_data *arena_data, int verbose);			// sti
void    short_fork(t_process *process, t_data *arena_data, int verbose);				// fork
void    long_direct_load(t_process *process, t_data *arena_data, int verbose);			// lld
void    long_indirect_load(t_process *process, t_data *arena_data, int verbose);		// lldi
void    long_fork(t_process *process, t_data *arena_data, int verbose);					// lfork
void    aff(t_process *process, t_data *arena_data, int verbose);						// aff
#endif
