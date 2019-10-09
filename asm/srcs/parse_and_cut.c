/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_and_cut.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/04 16:48:28 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 17:37:26 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

char	*parse_and_cut_label(const char *str, t_champ **champ)
{
	int			i;
	t_command	*curr_command;

	i = 0;
	curr_command = NULL;
	if (!(curr_command = last_command(champ)))
			return (NULL);
	while (str[i] && ft_strctn(LABEL_CHARS, str[i]))
		i++;
	if (i > 0 && str[i] == LABEL_CHAR)
	{
		if ((curr_command->label || curr_command->op) && !(curr_command = next_command(&curr_command)))
			return (NULL);
		if (!(curr_command->label = ft_strsub(str, 0, i)))
			return (NULL);
		return (ft_strtrim(ft_strsub(str, i + 1, strlen(str) - (i + 1))));
	}
	return (ft_strtrim(ft_strdup(str)));
}

char	*parse_and_cut_op_name(const char *str, t_champ **champ)
{
	int			i;
	t_command	*curr_command;

	i = 0;
	curr_command = NULL;
	if (!(curr_command = last_command(champ)))
		return (NULL);
	if (op_exist(str))
	{
		if (curr_command->op && !(curr_command = next_command(&curr_command)))
			return (0);
		while (str[i] && !ft_strctn("\t ", str[i]))
			i++;
		curr_command->op = ft_strsub(str, 0, i);
		return (ft_strtrim(ft_strsub(str, i + 1, strlen(str) - (i + 1))));
	}
	return (ft_strtrim(ft_strdup(str)));
}

char	*parse_and_cut_op_params(const char *str, t_champ **champ)
{
	t_command	*curr_command;
	char		**tab;
	int			i;

	curr_command = NULL;
	tab = NULL;
	i = 0;
	if (!(curr_command = last_command(champ)))
		return (NULL);
	if (count_char(str, SEPARATOR_CHAR) == op_param_count(curr_command->op) - 1)
	{
		if (!(tab = str_multisplit(str, "\t ,")))
			return (NULL);
	}
	if (!(curr_command->params = new_params(tab_length(tab))))
		return (NULL);
	while (tab[i])
	{
		curr_command->params[i]->value = strdup(tab[i]);
		i++;
	}
	return ("Line parsed !");
}