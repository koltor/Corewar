/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_command.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/04 16:48:28 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 17:11:59 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	parse_label(t_data **data, t_command **command)
{
	char		*tmp;
	int			i;

	tmp = NULL;
	i = 0;
	while ((*data)->line[i] && ft_strctn(LABEL_CHARS, (*data)->line[i]))
		i++;
	if (i > 0 && (*data)->line[i] == LABEL_CHAR)
	{
		if (((*command)->label || (*command)->op) &&
			!((*command) = next_command(command)))
			error_exit(strerror(errno), data);
		if (!((*command)->label = ft_strsub((*data)->line, 0, i)))
			error_exit(strerror(errno), data);
		i++;
		if (!(tmp = ft_strsub((*data)->line, i, ft_strlen((*data)->line) - i)))
			error_exit(strerror(errno), data);
		ft_strdel(&((*data)->line));
		(*data)->line = ft_strtrim_f(tmp);
	}
}

static void	parse_op(t_data **data, t_command **command)
{
	char		*tmp;
	int			i;

	tmp = NULL;
	i = 0;
	while ((*data)->line[i] && !ft_isspace((*data)->line[i]) &&
		(*data)->line[i] != DIRECT_CHAR)
		i++;
	if (!(tmp = ft_strsub((*data)->line, 0, i)))
		error_exit(strerror(errno), data);
	if (op_exist(tmp))
	{
		if ((*command)->op && !((*command) = next_command(command)))
			error_exit(strerror(errno), data);
		(*command)->op = tmp;
		if (!(tmp = ft_strsub((*data)->line, i, ft_strlen((*data)->line) - i)))
			error_exit(strerror(errno), data);
		ft_strdel(&((*data)->line));
		(*data)->line = ft_strtrim_f(tmp);
	}
	else
	{
		ft_strdel(&tmp);
		error_exit(ft_sprintf("Syntax error : %s", (*data)->line), data);
	}
}

static void	parse_params(t_data **data, t_command **command)
{
	char		**tab;
	int			i;

	tab = NULL;
	i = 0;
	if ((count_char((*data)->line, SEPARATOR_CHAR) !=
		op_param_count((*command)->op) - 1) ||
		!(tab = ft_strsplit((*data)->line, ',')))
		error_exit(ft_sprintf("Invalid parameter count for instruction %s",
			(*command)->op), data);
	if (!((*command)->params = new_params(tab_length((void **)tab))))
		error_exit(strerror(errno), data);
	while (tab[i])
	{
		if (!((*command)->params[i]->str = ft_strtrim_f(tab[i])))
			error_exit(strerror(errno), data);
		i++;
	}
	ft_memdel((void **)&tab);
}

void		parse_command(t_data **data)
{
	t_command	*command;

	command = NULL;
	if (!(*data)->champ->name || !(*data)->champ->comment)
		error_exit(ft_sprintf("Name and/or Comment aren't defined at the top \
of the file"), data);
	if (!ft_strctn(LABEL_CHARS, (*data)->line[0]))
		error_exit(ft_sprintf("Lexical error : %s", (*data)->line), data);
	if (!(command = last_command(&((*data)->champ))))
		error_exit(strerror(errno), data);
	parse_label(data, &command);
	if (ft_strlen((*data)->line) > 0)
		parse_op(data, &command);
	if (ft_strlen((*data)->line) > 0)
		parse_params(data, &command);
	else if (command->op)
		error_exit(ft_sprintf("No params for op : %s", command->op), data);
}
