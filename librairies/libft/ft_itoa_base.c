/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/25 19:44:23 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 12:58:31 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lsize(unsigned int nbr, int base)
{
	int	size;

	size = 0;
	if (nbr == 0)
		size++;
	while (nbr != 0)
	{
		nbr /= base;
		size++;
	}
	return (++size);
}

char		*ft_itoa_base(unsigned int value, int base)
{
	char			*rep;
	int				i;
	int				size;
	unsigned int	temp;

	if (base < 2 || base > 16)
		return (NULL);
	size = ft_lsize(value, base);
	i = -1;
	if (!(rep = ft_strnew(sizeof(char) * size)))
		return (NULL);
	while (++i < size - 1)
	{
		temp = value % base;
		value /= base;
		if ((temp = ft_abs(temp)) < 10 && size - 2 - i >= 0)
			rep[size - 2 - i] = temp + '0';
		else if (size - 2 - i >= 0)
			rep[size - 2 - i] = temp - 10 + 'A';
	}
	return (rep);
}
