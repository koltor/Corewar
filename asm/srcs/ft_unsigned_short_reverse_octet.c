/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unsigned_short_reverse_octet.c                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 14:41:06 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 12:03:49 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

unsigned short	unsigned_short_reverse_octet(unsigned short n)
{
	unsigned short rev;

	rev = n & 0xff00;
	rev = rev >> 8;
	n = n << 8;
	rev = rev | (n & 0xff00);
	return (rev);
}
