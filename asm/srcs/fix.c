/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fix.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 16:29:24 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 16:29:58 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	test_str_rest(t_data **data, int pos)
{
	pos++;
	while ((*data)->line[pos])
	{
		if (!ft_isspace((*data)->line[pos]))
			error_exit(ft_sprintf("Invalid char after second quote : %c\n",
				(*data)->line[pos]), data);
		pos++;
	}
}
