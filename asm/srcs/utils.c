/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 11:41:35 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 17:22:58 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		tab_length(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		error_exit(char *error_str)
{
	printf("%s\n", error_str);
	exit(1);
}

t_bool str_only_ctn(const char *str, const char *ctn)
{
	while (*str)
	{
		if (!ft_strctn(ctn, *str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

t_bool	ft_strctn(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (TRUE);
		str++;
	}
	return (FALSE);
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