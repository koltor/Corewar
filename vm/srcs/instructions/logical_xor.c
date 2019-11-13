/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   logical_xor.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:09:59 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 13:34:45 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void		logical_xor(t_process *proc, t_data *data, int verbose)
{
	get_params(data, proc);
	if (!compute_params(data, proc))
		return ;
	proc->reg[proc->param[2] - 1] =
		(proc->param_value[0] ^ proc->param_value[1]) % IDX_MOD;
	proc->carry = proc->reg[proc->param[2] - 1] == 0 ? 1 : 0;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		dprintf(1, "P %4d | xor %d %d r%d\n", proc->id,
			proc->param_value[0], proc->param_value[1], proc->param[2]);
}
