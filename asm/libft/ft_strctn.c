/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strctn.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 13:08:16 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/13 13:23:32 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_strctn(const char *str, char c)
{
	if (str)
	{
		while (*str)
		{
			if (*str++ == c)
				return (TRUE);
		}
	}
	return (FALSE);
}
