/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_short_reverse_octet.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 14:41:06 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 16:36:29 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

short	short_reverse_octet(short n)
{
	short rev;

	rev = n & 0xff00;
	rev = rev >> 8;
	n = n << 8;
	rev = rev | (n & 0xff00);
	return (rev);
}
