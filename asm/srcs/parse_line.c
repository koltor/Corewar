/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_line.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 17:27:33 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 16:30:01 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	clean_line(t_data **data)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while ((*data)->line[i] && !ft_strctn(COMMENT_CHARS, (*data)->line[i]))
		i++;
	if (!(tmp = ft_strsub((*data)->line, 0, i)))
		error_exit(ft_sprintf("%s", strerror(errno)), data);
	ft_strdel(&((*data)->line));
	if (!((*data)->line = ft_strtrim_f(tmp)))
		error_exit(ft_sprintf("%s", strerror(errno)), data);
}

static int	find_first_quote_index(t_data *data, const char *command)
{
	unsigned int	i;

	i = 0;
	while (data->line[i] && ft_isspace(data->line[i]))
		i++;
	i += ft_strlen(command);
	while (data->line[i] && ft_isspace(data->line[i]))
		i++;
	if (data->line[i] != '\"')
		error_exit(ft_sprintf("Bad char %c\n", data->line[i]), &data);
	return (++i);
}

static void	construct_str(t_data **data, int first, char **tmp)
{
	unsigned int i;

	i = first;
	while ((*data)->line[i] != '\"')
	{
		while ((*data)->line[i] && (*data)->line[i] != '\"')
			i++;
		if ((*data)->line[i] != '\"')
		{
			*tmp = ft_strjoin_f(*tmp, &((*data)->line[first]), 1);
			*tmp = ft_strjoin_f(*tmp, "\n", 1);
			first = 0;
			i = 0;
			ft_strdel(&((*data)->line));
			if (get_next_line((*data)->fd, &((*data)->line)) == 0)
				error_exit(ft_sprintf("No second \"\n"), data);
		}
		else
			*tmp = ft_strjoin_f(*tmp, ft_strsub((*data)->line,
										first, i - first), 3);
	}
	test_str_rest(data, i);
}

static void	parse_between_quotes(t_data **data, char *command)
{
	int				i;
	unsigned int	first;
	char			*tmp;

	tmp = NULL;
	i = find_first_quote_index(*data, command);
	first = i;
	if ((*data)->line[i] == '\"')
	{
		test_str_rest(data, i);
		tmp = ft_strnew(0);
	}
	else
		construct_str(data, first, &tmp);
	if (!ft_strcmp(command, NAME_CMD_STRING) && !(*data)->champ->name)
		(*data)->champ->name = tmp;
	if (!ft_strcmp(command, COMMENT_CMD_STRING) && !(*data)->champ->comment)
		(*data)->champ->comment = tmp;
}

void		parse_line(t_data **data)
{
	int		i;

	i = 0;
	while (ft_isspace((*data)->line[i]))
		i++;
	if (!ft_strncmp(&((*data)->line[i]), NAME_CMD_STRING,
								ft_strlen(NAME_CMD_STRING)))
		parse_between_quotes(data, NAME_CMD_STRING);
	else if (!ft_strncmp(&((*data)->line[i]), COMMENT_CMD_STRING,
									ft_strlen(COMMENT_CMD_STRING)))
		parse_between_quotes(data, COMMENT_CMD_STRING);
	else if (ft_strncmp(&((*data)->line[i]), EXTEND_CMD_STRING,
									ft_strlen(EXTEND_CMD_STRING)))
	{
		clean_line(data);
		if (ft_strlen((*data)->line) > 0 &&
			!ft_strctn(COMMENT_CHARS, (*data)->line[0]))
			parse_command(data);
	}
}
