/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/25 17:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 14:05:04 by matheme     ###    #+. /#+    ###.fr     */
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

# define LIST_OPTION "ndvg"

/*****************************
 * definition des structures *
******************************/
typedef struct			s_option
{
	char				expected_arg;
	unsigned int		dump;
	int					fd[MAX_PLAYERS];
	int					n[MAX_PLAYERS];
	int					nb_champ;
	int					option;
}						t_option;

typedef struct			s_data
{
	unsigned int		cycle;
	unsigned int		nb_live;
	unsigned int		nb_check;
	int					cycle_to_die;
	char				arena[MEM_SIZE];
}						t_data;

typedef struct			s_process
{
	char				registe[16];
	
	int					is_alive;
	int					carry;
	unsigned int		id;
}						t_process;


/******************************************
 * Fonction d'initialisation de structure *
*******************************************/
void	init_arena_data(t_data *arena_data);
void	init_arg_data(t_option *arg_data);

/***********************
 * Fonction de parsing *
************************/
# define OUVRE_UN_FICHIER 0
# define RECUPERE_OPTIONS 1
# define RECUPERE_VALEURS 2

void	process_arg(t_option *arg_data, int ac, char **av);
void	get_value_for(char *str, t_option *arg_data);
void	get_option(char *str, t_option *arg_data);
void	get_champ(char *champ_path, t_option *arg_data);

void	process_champ(t_option arg_data, t_header (*header)[MAX_PLAYERS], char *arena);
void	get_data_of_champ(t_header *header, const char src[]);

/*********************
 * Fonction d'erreur *
**********************/
void	invalid_champs(void);
void	usage(void);

/************************
 * Fonction de debugage *
*************************/
void	show_struct_option(t_option arg_data);

/**************************************************************************
 * Fonction de on sait pas trop dans quel case les mettres pour l'instant *
***************************************************************************/
void	hexdump(void *mem, unsigned int len);

/*********************
 * Fonction de libft *
**********************/
long	ft_atol(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *b, size_t n);
#endif
