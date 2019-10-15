/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 13:06:27 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/12 15:46:21 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#ifndef ASM_H
# define ASM_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "op.h"
# define USAGE "Usage: ./asm [-a] <sourcefile.s>\n\
\t-a : Instead of creating a .cor file, outputs a stripped and annotated \
version of the code to the standard output\n"

typedef struct	s_param
{
	t_arg_type	type;
	int			size; 
	int			code;
	char		*str;
	int			value;
}				t_param;

typedef struct	s_command
{
	int					index;
	int					size;
	unsigned char		ocp;
	char				*label;
	char				*op;
	t_param				**params;
	struct s_command	*next_command;
}				t_command;

typedef struct	s_champ
{
	char		*name;
	char		*comment;
	int			program_size;
	t_command	*command_list;
}				t_champ;

typedef struct	s_data
{
	char	*file_name;
	t_bool	annote;
	int		fd;
	t_champ	*champ;
}				t_data;

extern t_op		op_tab[17];

/* Parsing */

void		parse_file(int fd, t_champ **champ);
void		parse_command(char const *str, t_champ **champ, int line_number);

/* Compute */

void		compute_champ(t_champ **champ);
void		compute_param(t_param *param, t_champ *champ, t_command *command);

/* Write */

void		write_header(int fd, t_champ *champ);
void		write_command(int fd, t_command *command);
void		write_1_byte(int value, int fd);
void		write_2_bytes(int value, int fd);
void		write_4_bytes(int value, int fd);

/* Op infos */

int			op_param_count(const char *name);
t_bool		op_exist(const char *name);
t_bool		op_has_ocp(const char *name);
t_bool		op_dir_size(const char *name);
int			op_code(const char *name);

/* Command list */

t_command	*last_command(t_champ **champ);
t_command	*next_command(t_command **command);

/* New struct */

t_data		*new_data(void);
t_champ		*new_champ(void);
t_command	*new_command(void);
t_param		**new_params(int param_count);

/* Utils */

int			error_exit(char *error_str);
t_bool		label_exists(char *str, t_command *command_list);
int			label_index(char *label, t_champ *champ);
char		**str_multisplit(char const *str, char const *separators);
t_bool		ft_strctn(const char *str, char c);
t_bool		str_only_ctn(const char *str, const char *ctn);
int			count_char(const char *str, char c);
int			tab_length(void **tab);
unsigned int	unsigned_int_reverse_octet(unsigned int n);
unsigned short	unsigned_short_reverse_octet(unsigned short n);

#endif