/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 14:25:40 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 11:07:54 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	i;
	size_t			res;
	int				sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '-' || str[i] == '+')
			sign = str[i++] == '-' ? -sign : sign;
		while (ft_isdigit(str[i]))
			res = 10 * res + (str[i++] - '0');
		return ((int)(sign * res));
	}
	return (0);
}
