/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jump_if_zero.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:10:39 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 15:14:02 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	jump_if_zero(t_process *proc, t_data *data, int verbose)
{
	transfer_in_proc(data, proc, 0, proc->pc + 1);
	if (proc->carry == 1)
	{
		proc->pc = (proc->pc + (proc->param[0] % IDX_MOD)) % MEM_SIZE;
		if (verbose & VERBOSE_SHOW_OPERATIONS)
			dprintf(1, "P %4d | zjmp %d OK\n", proc->id, proc->param[0]);
	}
	else
	{
		if (verbose & VERBOSE_SHOW_OPERATIONS)
			dprintf(1, "P %4d | zjmp %d FAILED\n", proc->id, proc->param[0]);
	}
}
