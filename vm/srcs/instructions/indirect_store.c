/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   indirect_store.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:11:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 17:09:51 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void		indirect_store(t_process *proc, t_data *data, int verbose)
{
	int	pos;

	get_params(data, proc);
	if (!compute_params(data, proc))
		return ;
	pos = (proc->param_value[1] + proc->param_value[2]) % IDX_MOD;
	transfer_on_ram(data, proc, 0, pos);
	if (data->visu)
		print_footprint((MEM_SIZE + proc->pc + pos) % MEM_SIZE, 4,
			proc->id_player + 1);
	if (verbose & VERBOSE_SHOW_OPERATIONS)
	{
		ft_printf("P %4d | sti r%d %d %d\n", proc->id,
			proc->param[0], proc->param_value[1], proc->param_value[2]);
		print_space_for_indirect(proc->id);
		ft_printf("| -> store to %d + %d = %d (with pc and mod %d)\n",
			proc->param_value[1], proc->param_value[2],
			(proc->param_value[1] + proc->param_value[2]), (proc->pc + pos));
	}
}
