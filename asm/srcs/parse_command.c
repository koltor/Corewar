/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_command.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/04 16:48:28 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/12 15:46:19 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char	*parse_label(const char *str, t_champ **champ)
{
	t_command	*curr_command;
	char		*rest;
	int			i;

	curr_command = NULL;
	rest = NULL;
	i = 0;
	if (!(curr_command = last_command(champ)))
		error_exit(strerror(errno));
	while (str[i] && ft_strctn(LABEL_CHARS, str[i]))
		i++;
	if (i > 0 && str[i] == LABEL_CHAR)
	{
		if ((curr_command->label || curr_command->op) &&
			!(curr_command = next_command(&curr_command)))
			error_exit(strerror(errno));
		if (!(curr_command->label = ft_strsub(str, 0, i)))
			error_exit(strerror(errno));
		i++;
		if (!(rest = ft_strsub(str, i, strlen(str) - i)))
			error_exit(strerror(errno));
		return (ft_strtrim(rest));
	}
	return (ft_strtrim(str));
}

static char	*parse_op(const char *str, t_champ **champ)
{
	t_command	*curr_command;
	char		*rest;
	int			i;

	curr_command = NULL;
	rest = NULL;
	i = 0;
	if (!(curr_command = last_command(champ)))
		error_exit(strerror(errno));
	while (str[i] && !ft_strctn("\t ", str[i]))
		i++;
	if (!(rest = ft_strsub(str, 0, i)))
		error_exit(strerror(errno));
	if (op_exist(rest))
	{
		if (curr_command->op &&
			!(curr_command = next_command(&curr_command)))
			error_exit(strerror(errno));
		curr_command->op = ft_strdup(rest);
		i++;
		rest = ft_strsub(str, i, strlen(str) - i);
		return (ft_strtrim(rest));
	}
	return (ft_strtrim(str));
}

static void	parse_params(const char *str, t_champ **champ)
{
	t_command	*curr_command;
	char		**tab;
	int			i;

	curr_command = NULL;
	tab = NULL;
	i = 0;
	if (!(curr_command = last_command(champ)))
		error_exit(strerror(errno));
	if (count_char(str, SEPARATOR_CHAR) == op_param_count(curr_command->op) - 1)
	{
		if (!(tab = str_multisplit(str, "\t ,")))
			error_exit(strerror(errno));
	}
	if (!(curr_command->params = new_params(tab_length((void **)tab))))
		error_exit(strerror(errno));
	while (tab[i])
	{
		if (!(curr_command->params[i]->str = ft_strdup(tab[i])))
			error_exit(strerror(errno));
		i++;
	}

}

void		parse_command(char const *str, t_champ **champ, int line_number)
{
	char	*str_rest;

	str_rest = NULL;
	if (!(*champ)->name || !(*champ)->comment)
		error_exit("Syntax error at token");
	if (!ft_strctn(LABEL_CHARS, str[0]))
	{
		printf("Lexical error at [%d:1]\n", line_number);
		error_exit(NULL);
	}
	if (!(str_rest = parse_label(str, champ)))
		error_exit("Label parsing error");
	if (strlen(str_rest) > 0 && !(str_rest = parse_op(str_rest, champ)))
		error_exit("op");
	if (strlen(str_rest) > 0)
		parse_params(str_rest, champ);
}