/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_process.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 14:05:40 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 12:49:05 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void		process_move(t_process *proc, t_data *data, int verbose)
{
	int		old_pc;
	char	op_size;

	if (proc->opc_curr == 0x09 && proc->carry)
		return ;
	old_pc = proc->pc;
	op_size = (proc->opc_curr == 0) ? 1 : proc->curr_op_size;
	proc->curr_op_size = 0;
	proc->pc = (proc->pc + op_size) % MEM_SIZE;
	if (verbose & VERBOSE_SHOW_PC_MOVEMENTS && proc->to_move == TRUE)
	{
		ft_printf("ADV %hhd (0x%.4x -> 0x%.4x) ", op_size, old_pc,
			old_pc + op_size);
		print_memory_memsize(data->arena, op_size, old_pc);
	}
}
