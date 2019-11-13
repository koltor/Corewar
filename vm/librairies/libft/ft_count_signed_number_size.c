/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_signed_number_size.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 16:47:25 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 16:50:58 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		count_signed_number_size(long long n)
{
	int cpt;

	cpt = 0;
	if (n == 0)
		cpt = 1;
	while (n != 0)
	{
		n = n / 10;
		cpt++;
	}
	return (cpt);
}
