/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   affect_new_opc.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/08 17:45:00 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 17:46:24 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	affect_new_opc(t_process *proc, t_data *data)
{
	if (data->arena[proc->pc] >= 0x01 && data->arena[proc->pc] <= 0x10)
	{
		proc->opc_curr = data->arena[proc->pc];
		proc->cycle = g_op_tab[proc->opc_curr - 1].cycles;
		return ;
	}
	proc->to_move = false;
	proc->valid_op = false;
	proc->opc_curr = 0;
	proc->cycle = 1;
}
