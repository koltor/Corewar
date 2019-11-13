/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compute_params.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 11:37:15 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 15:04:05 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int		get_index(t_data *data, t_process *proc, int val)
{
	int	res;
	int	pos;

	res = 0;
	pos = (proc->pc + (val % IDX_MOD));
	pos %= MEM_SIZE;
	while (pos < 0)
		pos += MEM_SIZE;
	res |= (unsigned char)data->arena[pos] << 24;
	res |= (unsigned char)data->arena[pos + 1] << 16;
	res |= (unsigned char)data->arena[pos + 2] << 8;
	res |= (unsigned char)data->arena[pos + 3];
	return (res);
}

static t_bool	compute_registers(t_data *data, t_process *proc)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (get_param_type(proc->ocp_curr, i + 1) == REG_CODE)
		{
			if (proc->param[i] < 1 || proc->param[i] > REG_NUMBER)
				return (FALSE);
			proc->param_value[i] = proc->reg[proc->param[i] - 1];
		}
		i++;
	}
	return (TRUE);
}

static void		compute_directs(t_data *data, t_process *proc)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (get_param_type(proc->ocp_curr, i + 1) == DIR_CODE)
			proc->param_value[i] = proc->param[i];
		i++;
	}
}

static void		compute_indirects(t_data *data, t_process *proc)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (get_param_type(proc->ocp_curr, i + 1) == IND_CODE)
			proc->param_value[i] = get_index(data, proc, proc->param[i]);
		i++;
	}
}

t_bool			compute_params(t_data *data, t_process *proc)
{
	if (!compute_registers(data, proc))
		return (FALSE);
	compute_indirects(data, proc);
	compute_directs(data, proc);
	return (TRUE);
}
