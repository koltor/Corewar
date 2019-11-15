/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 09:58:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 15:03:14 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** max_check_live verirfie le nombre de live effectuer pendant toute la durée
** d'un cycle de die et le max_check
** decremente cycle_to_die de cycle_delta en cas de besoin
*/

static void		max_check_live(t_data *data)
{
	if (data->nb_live >= NBR_LIVE)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->nb_check = 0;
		if (data->verbose & VERBOSE_SHOW_CYCLES)
			ft_printf("Cycle to die is now %d\n", data->cycle_to_die);
	}
	else if (data->nb_check == MAX_CHECKS)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->nb_check = 0;
		if (data->verbose & VERBOSE_SHOW_CYCLES)
			ft_printf("Cycle to die is now %d\n", data->cycle_to_die);
	}
}

/*
** cycle_to_die est appelé à chaque fois que l'on arrive à une fin de cycle
** la fonction remet les compteurs à 0 et augmente le nombre de check_realisé
** cycle_to_die s'occupe également de diminuer le cycle_to_die si besoin
** elle s'occupe egalement de supprimer tous les process mort
*/

static t_bool	cycle_to_die(t_data *data, long *l_cycle)
{
	data->nb_check += 1;
	*l_cycle = 0;
	kill_dead_process(data);
	max_check_live(data);
	data->nb_live = 0;
	data->visu ? set_live_visu_bzero() : 0;
	if (data->living_process == 0)
		return (TRUE);
	return (FALSE);
}

/*
** cycle generale des combats et des regles de corewar
** check_le numero de cycle.
** appele chaque processus pour executer leur action.
** incremente le nombre de cycle à chaque tour de boucle
*/

void			cycle(t_data *data)
{
	long cycle_local;

	cycle_local = 0;
	while (++data->cycle != data->dump + 1)
	{
		cycle_local++;
		if (data->verbose & VERBOSE_SHOW_CYCLES)
			ft_printf("It is now cycle %ld\n", data->cycle);
		browse_process(data);
		if (cycle_local >= data->cycle_to_die)
			if (cycle_to_die(data, &cycle_local))
				break ;
		if (data->visu && !loop_corewar(data, cycle_local))
			break ;
	}
	if (data->cycle == data->dump + 1)
		ft_hexdump(data->arena, MEM_SIZE);
	if (data->living_process != 0)
		clean_list(data->pchain);
	data->visu ? show_the_winner(data, cycle_local) : 0;
}
