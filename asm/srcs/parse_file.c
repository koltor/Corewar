/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 17:27:33 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/12 15:46:22 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	clean_line(const char *src, char **dest)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != ';' && src[i] != COMMENT_CHAR)
		i++;
	if (!(*dest = ft_strsub(src, 0, i)))
		error_exit(strerror(errno));
	if (!(*dest = ft_strtrim(*dest)))
		error_exit(strerror(errno));
}

static void	parse_prog_name(const char *str, t_champ **champ)
{
	int i;
	int	start;
	int	end;

	i = strlen(NAME_CMD_STRING);
	while (str[i] && ft_strctn(" \t", str[i]))
		i++;
	if (str[i] == '\"')
		start = i++;
	else
		error_exit("ERROR");
	while (str[i] && str[i] != '\"')
		i++;
	if (str[i])
		end = i++;
	if (str[i])
		error_exit("ERROR");
	else
		(*champ)->name = ft_strsub(str, start + 1, end - start - 1);
}

static void	parse_prog_comment(const char *str, t_champ **champ)
{
	int i;
	int	start;
	int	end;

	i = strlen(COMMENT_CMD_STRING);
	while (str[i] && ft_strctn(" \t", str[i]))
		i++;
	if (str[i] == '\"')
		start = i++;
	else
		error_exit("ERROR");
	while (str[i] && str[i] != '\"')
		i++;
	if (str[i])
		end = i++;
	if (str[i])
		error_exit("ERROR");
	else
		(*champ)->comment = ft_strsub(str, start + 1, end - start - 1);
}

void		parse_file(int fd, t_champ **champ)
{
	char	*line;
	char	*cleaned_line;
	int		line_number;

	line = NULL;
	cleaned_line = NULL;
	line_number = 0;
	while(get_next_line(fd, &line) > 0)
	{
		line_number++;
		clean_line(line, &cleaned_line);
		if (!strncmp(cleaned_line, NAME_CMD_STRING, strlen(NAME_CMD_STRING)))
			parse_prog_name(cleaned_line, champ);
		else if (!strncmp(cleaned_line, COMMENT_CMD_STRING, strlen(COMMENT_CMD_STRING)))
			parse_prog_comment(cleaned_line, champ);
		else if (strlen(cleaned_line) > 0 && cleaned_line[0] != COMMENT_CHAR && cleaned_line[0] != ';')
			parse_command(cleaned_line, champ, line_number);
	}
}