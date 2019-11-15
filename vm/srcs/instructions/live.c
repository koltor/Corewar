/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   live.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:02:43 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 17:09:51 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int	is_there(unsigned int value, unsigned int *tab, int max_p)
{
	int i;

	i = -1;
	while (++i < max_p)
		if (tab[i] == value)
			return (i);
	return (-1);
}

void		live(t_process *proc, t_data *data, int verbose)
{
	int idx;

	get_params(data, proc);
	proc->param_value[0] = proc->param[0];
	proc->is_alive = 1;
	data->nb_live += 1;
	proc->last_live = data->cycle;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		ft_printf("P %4d | live %d\n", proc->id, proc->param_value[0]);
	if ((idx = is_there(proc->param_value[0], data->n, data->nb_champ)) != -1)
	{
		data->last_player_alive = idx;
		data->visu ? set_live_visu(idx + 1) : 0;
		if (verbose & VERBOSE_SHOW_LIVES)
			ft_printf("Player %d (%s) is said to be alive\n", idx + 1,
			data->champs_data[idx].prog_name);
	}
}
