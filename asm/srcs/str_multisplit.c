/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_multisplit.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 14:14:18 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 15:51:46 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int	ft_countwords(char const *str, char const *separators)
{
	unsigned int count;

	count = 0;
	while (*str)
	{
		if (ft_strctn(separators, *str))
			str++;
		if (*str && !ft_strctn(separators, *str))
		{
			count++;
			while (*str && !ft_strctn(separators, *str))
				str++;
		}
	}
	return (count);
}

static int	ft_wordlength(char const *str, char const *separators)
{
	unsigned int length;

	length = 0;
	while (*str && !ft_strctn(separators, *str))
	{
		str++;
		length++;
	}
	return (length);
}

char		**str_multisplit(char const *str, char const *separators)
{
	char			**tab;
	unsigned int	i;

	if (str)
	{
		if (!(tab = (char **)malloc(sizeof(char *) * (ft_countwords(str, separators) + 1))))
			return (NULL);
		i = 0;
		while (*str)
		{
			if (ft_strctn(separators, *str))
				str++;
			if (*str && !ft_strctn(separators, *str))
			{
				if (!(tab[i++] = ft_strsub(str, 0, ft_wordlength(str, separators))))
					return (NULL);
			}
			while (*str && !ft_strctn(separators, *str))
				str++;
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}
