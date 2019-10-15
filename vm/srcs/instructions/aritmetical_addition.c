/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aritmetical_addition.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:06:51 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 12:56:11 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	aritmetical_addition(t_process *process, t_data *arena_data, int verbos)
{
	char ocp;
	char r[3];

	ft_memcpy(&ocp, &arena_data->arena[process->pc + 1], 1);
	ft_memcpy(&r[0], &arena_data->arena[process->pc + 2], 1);
	ft_memcpy(&r[1], &arena_data->arena[process->pc + 3], 1);
	ft_memcpy(&r[2], &arena_data->arena[process->pc + 4], 1);
	if (r[0] <= 0 || r[1] <= 0 || r[2] <= 0 || r[0] >= 17 || r[1] >= 17 || r[2] >= 17)
		return ;
	process->reg[r[2] - 1] = process->reg[r[1] - 1] + process->reg[r[0] - 1];
	if (process->reg[r[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	if (verbos & VERBOSE_SHOW_OPERATIONS)
		FP("P%5d | add r%hhd r%hhd r%hhd\n", process->id, r[0], r[1], r[2]);
}
