/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 17:27:33 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 17:37:39 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char	*clean_line(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ';' && str[i] != COMMENT_CHAR)
		i++;
	return (ft_strtrim(ft_strsub(str, 0, i)));
}

static char	*get_cmd_string_value(char const *str, int i)
{
	int first_coma_pos;
	int last_coma_pos;

	first_coma_pos = 0;
	last_coma_pos = 0;
	while (str[i] && ft_strctn(" \t", str[i]))
		i++;
	if (str[i] == '\"')
		first_coma_pos = i++;
	else
		return (NULL);
	while (str[i] && str[i] != '\"')
		i++;
	if (str[i])
		last_coma_pos = i++;
	else
		return (NULL);
	if (str[i])
		return(NULL);
	else
		return(ft_strsub(str, first_coma_pos + 1, last_coma_pos - first_coma_pos - 1));
}

static int	parse_command(char const *str, t_champ **champ)
{
	char	*str_rest;

	str_rest = NULL;
	if (!(str_rest = parse_and_cut_label(str, champ)))
		return (0);
	if (strlen(str_rest) > 0 && !(str_rest = parse_and_cut_op_name(str_rest, champ)))
		return (0);
	if (strlen(str_rest) > 0 && !(parse_and_cut_op_params(str_rest, champ)))
		return (0);
	return (1);
}

void		parse_file(int fd, t_champ **champ)
{
	char *line;
	char *cleaned_line;

	line = NULL;
	while(get_next_line(fd, &line) > 0)
	{
		if (!(cleaned_line = clean_line(line)))
			error_exit("Cleaning line error !");
		if (!strncmp(cleaned_line, NAME_CMD_STRING, strlen(NAME_CMD_STRING)))
		{
			if (!((*champ)->name = get_cmd_string_value(cleaned_line, strlen(NAME_CMD_STRING))))
				error_exit("Program name parsing error !");
		}
		else if (!strncmp(cleaned_line, COMMENT_CMD_STRING, strlen(COMMENT_CMD_STRING)))
		{
			if (!((*champ)->comment = get_cmd_string_value(cleaned_line, strlen(COMMENT_CMD_STRING))))
				error_exit("Program comment parsing error !");
		}
		else if (strlen(cleaned_line) > 0 && cleaned_line[0] != COMMENT_CHAR && cleaned_line[0] != ';')
		{
			if (!(*champ)->name || !(*champ)->comment || !parse_command(cleaned_line, champ))
				error_exit("Command parsing error !");
		}
	}
}