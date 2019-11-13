/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_space.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 14:01:36 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 14:00:07 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	print_space_for_indirect(int nb)
{
	int		size;
	char	space[20];

	ft_memset(space, ' ', 20);
	size = ft_nblen(nb);
	size += 3;
	size = (size < 7) ? 7 : 7;
	write(1, &space, size);
}
