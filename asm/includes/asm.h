/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 13:06:27 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 16:29:55 by kgrosjea    ###    #+. /#+    ###.fr     */
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

# define USAGE_1 "Usage: ./asm [-a] <sourcefile.s>\n\t-a : Instead of creating"
# define USAGE_2 " a .cor file, outputs a stripped and annotated version of the"
# define USAGE_3 " code to the standard output"

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
	int		fd;
	char	*line;
	t_champ	*champ;
}				t_data;

extern t_op		g_op_tab[17];

/*
**Parsing
*/

void			parse_line(t_data **data);
void			parse_command(t_data **data);

/*
**Compute
*/

void			compute_champ(t_data **data);
void			compute_param(t_param *param, t_data **data,
							t_command *command, int arg_pos);

/*
**Write
*/

void			write_header(t_data *data);
void			write_command(t_data *data, t_command *command);

/*
**Op infos
*/

int				op_param_count(const char *name);
t_bool			op_exist(const char *name);
t_bool			op_has_ocp(const char *name);
t_bool			op_dir_size(const char *name);
int				op_code(const char *name);
char			*param_type(int arg_type);

/*
**Command list
*/

t_command		*last_command(t_champ **champ);
t_command		*next_command(t_command **command);

/*
**New struct
*/

t_data			*new_data(void);
t_champ			*new_champ(void);
t_command		*new_command(void);
t_param			**new_params(int param_count);

/*
**Utils
*/

void			test_str_rest(t_data **data, int pos);
int				error_exit(char *error_str, t_data **data);
t_bool			label_exists(char *str, t_command *command_list);
int				label_index(char *label, t_data **data);
char			**str_multisplit(char const *str, char const *separators);
t_bool			str_only_ctn(const char *str, const char *ctn);
int				count_char(const char *str, char c);
int				tab_length(void **tab);
void			free_data(t_data **data);

#endif
