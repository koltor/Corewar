/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aritmetical_addition.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:06:51 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 13:35:13 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	aritmetical_addition(t_process *proc, t_data *data, int verbose)
{
	get_params(data, proc);
	if (!compute_params(data, proc))
		return ;
	proc->reg[proc->param[2] - 1] =
		(proc->param_value[0] + proc->param_value[1]) % IDX_MOD;
	proc->carry = proc->reg[proc->param[2] - 1] == 0 ? 1 : 0;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		dprintf(1, "P %4d | add r%hhd r%hhd r%hhd\n", proc->id,
			(char)proc->param[0], (char)proc->param[1], (char)proc->param[2]);
}
