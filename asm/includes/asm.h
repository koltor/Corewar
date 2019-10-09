/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 13:06:27 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 17:54:52 by kgrosjea    ###    #+. /#+    ###.fr     */
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
	char		*value;
}				t_param;

typedef struct	s_command
{
	int					index;
	int					size;
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

/* Compute and check */

void		compute_and_check(t_champ **champ);

/* Op infos */

int			op_param_count(const char *name);
t_bool		op_exist(const char *name);
t_bool		op_has_ocp(const char *name);
t_bool		op_dir_size(const char *name);

/* Command list */

t_command	*last_command(t_champ **champ);
t_command	*next_command(t_command **command);

/* Parse and cut */

char		*parse_and_cut_label(const char *str, t_champ **champ);
char		*parse_and_cut_op_name(const char *str, t_champ **champ);
char		*parse_and_cut_op_params(const char *str, t_champ **champ);

/* New struct */

t_data		*new_data(void);
t_champ		*new_champ(void);
t_command	*new_command(void);
t_param		**new_params(int param_count);

/* Utils */

int			error_exit(char *error_str);
void		debug(t_champ *champ);
char		**str_multisplit(char const *str, char const *separators);
t_bool		ft_strctn(const char *str, char c);
t_bool		str_only_ctn(const char *str, const char *ctn);
int			count_char(const char *str, char c);
int			tab_length(char **tab);

#endif