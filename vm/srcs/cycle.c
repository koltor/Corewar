/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   g_cycle.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 09:58:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 12:53:57 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** max_check_live verirfie le nombre de live effectuer pendant toute la durée
** d'un cycle de die et le max_check
** decremente cycle_to_die de cycle_delta en cas de besoin
*/

static void		max_check_live(t_data *arena_data)
{
	if (arena_data->nb_live >= NBR_LIVE)
	{
		arena_data->cycle_to_die -= CYCLE_DELTA;
		arena_data->nb_check = 0;
		if (arena_data->verbose & VERBOSE_SHOW_CYCLES)
			FP("Cycle to die is now %d\n", arena_data->cycle_to_die);
	}
	else if (arena_data->nb_check == MAX_CHECKS)
	{
		arena_data->cycle_to_die -= CYCLE_DELTA;
		arena_data->nb_check = 0;
		if (arena_data->verbose & VERBOSE_SHOW_CYCLES)
			FP("Cycle to die is now %d\n", arena_data->cycle_to_die);
	}
}

/*
** cycle_to_die est appelé à chaque fois que l'on arrive à une fin de cycle
** la fonction remet les compteurs à 0 et augmente le nombre de check_realisé
** cycle_to_die s'occupe également de diminuer le cycle_to_die si besoin
** elle s'occupe egalement de supprimer tous les process mort
*/

static t_bool	cycle_to_die(t_data *arena_data, unsigned long long *l_cycle)
{
	arena_data->nb_check += 1;
	*l_cycle = 0;
	max_check_live(arena_data);
	arena_data->nb_live = 0;
	kill_dead_process(arena_data);
	if (arena_data->living_process == 0 || arena_data->cycle_to_die <= 0)
		return (true);
	return (false);
}

/*
** cycle generale des combats et des regles de corewar
** check_le numero de cycle.
** appele chaque processus pour executer leur action.
** incremente le nombre de cycle à chaque tour de boucle
*/

void			cycle(t_data *arena_data)
{
	unsigned long long cycle_local;

	cycle_local = 0;
	while (++arena_data->cycle != arena_data->dump)
	{
		cycle_local++;
		if (arena_data->verbose & VERBOSE_SHOW_CYCLES)
			FP("It is now cycle %llu\n", arena_data->cycle);
		browse_process(arena_data);
		if (cycle_local == arena_data->cycle_to_die)
			if (cycle_to_die(arena_data, &cycle_local))
				break ;
	}
	if (arena_data->cycle == arena_data->dump)
		ft_hexdump(arena_data->arena, MEM_SIZE);
	if (arena_data->living_process != 0)
		clean_list(arena_data->pchain);
}
