/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   logical_xor.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:09:59 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 10:34:44 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	logical_xor(t_process *proc, t_data *arena_data, int verbose)
{
	char				*r;
	int					tmp;
	int					params[2];
	unsigned char		reg;

	ft_bzero(params, 8);
	ft_memcpy(&params[0], &arena_data->arena[proc->pc + 2], proc->size_params[0]);
	ft_memcpy(&params[1], &arena_data->arena[proc->pc + 2 + proc->size_params[0]], proc->size_params[1]);
	if (proc->size_params[0] == 1)
		params[0] = proc->reg[params[0] - 1];
	if (proc->size_params[1] == 1)
		params[1] = proc->reg[params[1] - 1];
	convert_params(params, proc);
	tmp = (int)params[0] ^ (int)params[1];
	ft_memcpy(&reg, &arena_data->arena[proc->pc + 2 + proc->size_params[0] + proc->size_params[1]], 1);
	proc->reg[reg] = tmp;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
	{
		if (proc->size_params[0] == 1)
			params[0] = (int)proc->reg[params[0]];
		if (proc->size_params[1] == 1)
			params[1] = (int)proc->reg[params[1]];
		FP("P%5d | xor %hhd %hhd r%d\n", proc->id, (char)params[0], (char)params[1], (unsigned char)reg);
	}
}
