/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   direct_store.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:04:03 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 17:09:51 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	direct_store(t_process *proc, t_data *data, int verbose)
{
	get_params(data, proc);
	if (!compute_params(data, proc))
		return ;
	if (get_param_type(proc->ocp_curr, 2) == REG_CODE)
		proc->reg[proc->param[1] - 1] = proc->param_value[0];
	else
	{
		transfer_on_ram(data, proc, 0, (proc->param[1] % IDX_MOD));
		if (data->visu)
			print_footprint(((proc->param[1] % IDX_MOD) + proc->pc) % MEM_SIZE,
				4, proc->id_player + 1);
	}
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		ft_printf("P %4d | st r%d %d\n", proc->id,
			proc->param[0], proc->param[1]);
}
