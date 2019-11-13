/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aff.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:14:47 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 13:34:45 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	aff(t_process *process, t_data *data, int verbose)
{
	char r1;

	ft_memcpy_memsize(&r1, &data->arena, process->pc + 2, 1);
	(void)verbose;
	process->carry = (process->reg[r1 - 1] == 0) ? 1 : 0;
}
