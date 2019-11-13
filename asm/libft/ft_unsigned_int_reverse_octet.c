/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unsigned_int_reverse_octet.c                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 14:43:17 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 14:43:55 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

unsigned int	unsigned_int_reverse_octet(unsigned int n)
{
	unsigned int rev;

	rev = n & 0xff000000;
	rev = rev >> 8;
	n = n << 8;
	rev = rev | (n & 0xff000000);
	rev = rev >> 8;
	n = n << 8;
	rev = rev | (n & 0xff000000);
	rev = rev >> 8;
	n = n << 8;
	rev = rev | (n & 0xff000000);
	return (rev);
}
