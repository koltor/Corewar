/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy_memsize.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 14:40:02 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 14:43:11 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	*ft_memcpy_memsize(void *dst, const void *src, int idx, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char*)dst)[i] = ((char*)src)[(i + idx) % MEM_SIZE];
		i++;
	}
	return ((void*)dst);
}
