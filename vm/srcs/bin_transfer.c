/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bin_transfer.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 22:16:27 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 17:12:11 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	transfer_in_proc(t_data *data, t_process *proc, int id, int pos)
{
	proc->param[id] = 0;
	if (proc->size_params[id] == 1)
	{
		proc->param[id] = data->arena[(pos % MEM_SIZE)];
	}
	else if (proc->size_params[id] == 2)
	{
		if (data->arena[((pos) % MEM_SIZE)] < 0)
			proc->param[id] |= 0xFFFF << 16;
		proc->param[id] |= ((unsigned char)data->arena[((pos) % MEM_SIZE)])
			<< 8;
		proc->param[id] |= (unsigned char)data->arena[((pos + 1) % MEM_SIZE)];
	}
	else if (proc->size_params[id] == 4)
	{
		proc->param[id] |= data->arena[(pos + 3) % MEM_SIZE] & 0xff;
		proc->param[id] |= data->arena[(pos + 2) % MEM_SIZE] << 8 & 0xff00;
		proc->param[id] |= data->arena[(pos + 1) % MEM_SIZE] << 16 & 0xff0000;
		proc->param[id] |= data->arena[(pos % MEM_SIZE)] << 24 & 0xff000000;
	}
}

void	transfer_on_ram(t_data *data, t_process *proc, int id, int pos)
{
	pos = (pos + proc->pc) % MEM_SIZE;
	while (pos < 0)
		pos += MEM_SIZE;
	data->arena[((pos + 3) % MEM_SIZE)] = proc->param_value[id];
	data->arena[((pos + 2) % MEM_SIZE)] = proc->param_value[id] >> 8;
	data->arena[((pos + 1) % MEM_SIZE)] = proc->param_value[id] >> 16;
	data->arena[(pos % MEM_SIZE)] = proc->param_value[id] >> 24;
}
