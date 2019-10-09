/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   live.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:02:43 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 14:47:32 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void    live(t_process *process, t_data *arena_data, int verbose)
{
    unsigned int params;

    ft_memcpy(&params, &arena_data->arena[process->pc + 1], 4);
    params = unsigned_int_reverse_octet(params);
    process->is_alive = 1;
	arena_data->nb_live += 1;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		FP("P    %d | live %u\n", process->id, params);
}
