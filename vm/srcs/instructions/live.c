/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   live.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:02:43 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 13:41:49 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static unsigned int	is_there(unsigned int value, unsigned int *tab)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (tab[i] == value)
			return (i);
	return (-1);
}

void		live(t_process *process, t_data *arena_data, int verbose)
{
	unsigned int	params;
	unsigned int	idx;

	ft_memcpy(&params, &arena_data->arena[process->pc + 1], 4);
	params = unsigned_int_reverse_octet(params);
	process->is_alive = 1;
	arena_data->nb_live += 1;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		FP("P%5d | live %u\n", process->id, params);
	if ((idx = is_there(params, arena_data->n)) != -1)
	{
		arena_data->last_player_alive = idx;
		if (verbose & VERBOSE_SHOW_LIVES)
			FP("Player %d (%s) is said to be alive\n", idx + 1,
			arena_data->champs_data[idx].prog_name);
	}
}
