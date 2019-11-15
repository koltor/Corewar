/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_params.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 13:48:29 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 16:56:27 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int	op_param_count(int opc)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (g_op_tab[i].code == opc)
			return (g_op_tab[i].param_count);
		i++;
	}
	return (0);
}

t_bool		op_has_ocp(int opc)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (g_op_tab[i].code == opc)
			return ((t_bool)g_op_tab[i].use_ocp);
		i++;
	}
	return (FALSE);
}

void		get_params(t_data *data, t_process *proc)
{
	int param_count;
	int param;
	int offset;

	param_count = op_param_count(proc->opc_curr);
	param = 0;
	offset = 1;
	if (op_has_ocp(proc->opc_curr))
		offset++;
	while (param < param_count)
	{
		transfer_in_proc(data, proc, param, proc->pc + offset);
		offset += proc->size_params[param];
		param++;
	}
}
