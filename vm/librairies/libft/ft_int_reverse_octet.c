/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_int_reverse_octet.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 15:34:54 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 15:38:07 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		int_reverse_octet(int n)
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
