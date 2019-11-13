/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unsigned_short_reverse_octet.c                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 16:36:05 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 16:37:12 by ocrossi     ###    #+. /#+    ###.fr     */
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
