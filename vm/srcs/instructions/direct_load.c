/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   direct_load.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:03:23 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 10:29:03 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static char	get_ocp_params(char ocp, char params)
{
	const char v[4] = {
		(ocp & 0xc0) >> 6, (ocp & 0x30) >> 4, (ocp & 0xc) >> 2, ocp & 0x3
	};

	return (v[params - 1]);
}

void	direct_load(t_process *process, t_data *arena_data, int verbose)
{
	char			ocp;
	unsigned int	params1;
	char			r1;

	params1 = 0;
	ft_memcpy(&ocp, &arena_data->arena[process->pc + 1], 1);
	if (get_ocp_params(ocp, 1) == 2)
	{
		ft_memcpy(&params1, &arena_data->arena[process->pc + 2], 4);
		ft_memcpy(&r1, &arena_data->arena[process->pc + 6], 1);
		params1 = unsigned_int_reverse_octet(params1);
	}
	else
	{
		ft_memcpy(&params1, &arena_data->arena[process->pc + 2], 2);
		ft_memcpy(&r1, &arena_data->arena[process->pc + 4], 1);
		params1 = (unsigned int)short_reverse_octet((short)params1);
	}
	process->reg[r1 - 1] = params1;
	if (process->reg[r1 - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		FP("P%5d | ld %u r%hhd\n", process->id, params1, r1);
}
