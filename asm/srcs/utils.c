/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 11:41:35 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 12:49:15 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

char	*param_type(int arg_type)
{
	if (arg_type == T_REG)
		return ("register");
	else if (arg_type == T_DIR)
		return ("direct");
	else if (arg_type == T_IND)
		return ("indirect");
	return ("unknown");
}

int		tab_length(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		error_exit(char *error_str, t_data **data)
{
	get_next_line((*data)->fd, NULL);
	if (*data)
		free_data(data);
	if (error_str)
		ft_printf("%s\n", error_str);
	ft_strdel(&error_str);
	exit(1);
}

t_bool	str_only_ctn(const char *str, const char *ctn)
{
	while (*str)
	{
		if (!ft_strctn(ctn, *str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int		count_char(const char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
