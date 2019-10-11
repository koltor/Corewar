/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jump_if_zero.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:10:39 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 13:53:56 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void    jump_if_zero(t_process *proc, t_data *arena_data, int verbose)
{
	char r1;
	char r2;
	short index;

	ft_memcpy(&r1, &arena_data->arena[proc->pc + 1], 1);
	ft_memcpy(&r2, &arena_data->arena[proc->pc + 2], 1);
	index = r2 + r1;
	index = (index > 0) ? index : index + 1; // test le cas ou zjmp saute sur lui mm
//	FP("zjump bonjour tour n %llu| value du jump %hd\n", arena_data->cycle, index);
	if (proc->carry == 1)
	{
		proc->pc = (proc->pc + index) % IDX_MOD;
		if (verbose & VERBOSE_SHOW_OPERATIONS)
			FP("P    %d | zjmp %d OK\n", proc->id, index);
	}
	else
	{
		proc->pc = (proc->pc + 3) % IDX_MOD;
		if (verbose & VERBOSE_SHOW_OPERATIONS)
			FP("P    %d | zjmp %d FAILED\n", proc->id, index);
	}
}
