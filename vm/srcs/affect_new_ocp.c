/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   affect_new_ocp.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/08 17:46:37 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 12:49:15 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	get_op_params(t_process *proc, t_data *data)
{
	if (proc->opc_curr == 0xF || proc->opc_curr == 0xC ||
	proc->opc_curr == 0x09)
	{
		proc->size_params[0] = 2;
		proc->curr_op_size = 3;
		proc->valid_ocp = TRUE;
		return ;
	}
	else if (proc->opc_curr == 0x01)
	{
		proc->size_params[0] = 4;
		proc->curr_op_size = 5;
		proc->valid_ocp = TRUE;
		return ;
	}
	else
		proc->curr_op_size = 2;
	proc->ocp_curr = data->arena[(proc->pc + 1) % MEM_SIZE];
	read_ocp(proc);
}

void		affect_new_ocp(t_process *proc, t_data *data)
{
	get_op_params(proc, data);
	if (proc->valid_ocp == TRUE)
	{
		proc->valid_op = TRUE;
		proc->to_move = TRUE;
	}
	else
	{
		proc->valid_op = FALSE;
		proc->to_move = TRUE;
	}
}
