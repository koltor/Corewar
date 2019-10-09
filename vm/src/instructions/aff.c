/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aff.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:14:47 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 17:30:51 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void    aff(t_process *process, t_data *arena_data, int verbose)
{
	char r1;

	ft_memcpy(&r1, &arena_data->arena[process->pc + 2], 1);
	if (ft_isprint(r1))
		FP("%c\n", r1);
	if (r1 == 0)
		process->carry = 1;
	else
		process->carry = 0;
}