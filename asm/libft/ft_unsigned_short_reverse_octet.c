/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unsigned_short_reverse_octet.c                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 13:14:48 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 13:16:43 by kgrosjea    ###    #+. /#+    ###.fr     */
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
