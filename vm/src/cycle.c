/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 09:58:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 17:01:10 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** max_check_live verirfie le nombre de live effectuer pendant toute la durée d'un
** cycle de die et le max_check
** decremente cycle_to_die de cycle_delta en cas de besoin
*/

static void     max_check_live(t_data *arena_data)
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
** free_process libere 1 proccess
*/

static void		free_process(void *data, size_t data_size)
{
    (void)data_size;
	ft_memdel(&data);
}


static t_list	*get_prev(t_list *elem, t_list *begin)
{
	t_list *res;

	res = begin;
	if (elem == begin)
		return (elem);
	while (res->next != elem)
		res = res->next;
	return (res);
}

/*
** kill_one_process supprime un process en particulier et recolle
** la liste brisé pour n'en faire qu'une.
** bv 1 : cas de suppression du premier process de la liste
** bv 2 : cas du dernier elément
** bv 3 : cas d'un process intermerdiaire
*/

void	kill_one_process(t_list *elem, t_data *arena_data, int bv)
{
	void	(*pf)(void*, size_t);
	t_list 	*prev;
	t_list *begin;

	begin = arena_data->pchain;
	pf = &free_process;
	if (bv == 2)
	{
		prev = get_prev(elem, begin);
		prev->next = NULL;
	}
	else if (bv == 3)
	{
		prev = get_prev(elem, begin);
		prev->next = elem->next;
	}
    ft_lstdelone(&elem, pf);
	arena_data->nb_process--;
	if (arena_data->nb_process == 0)
		arena_data->pchain = NULL;
	if (arena_data->nb_process == 1)
		(arena_data->pchain)->next = NULL;
}

/*
** boucle dans la chaine de process et del les elems en fonction de si ils sont au debut
** au milieu ou a la fin de la liste
*/

void	kill_dead_process(t_data *arena_data)
{
	t_list *current;
	t_list *to_del;

	current = arena_data->pchain;
	while (current)
	{
		to_del = current;
		current = current->next;
		if (((t_process *)(to_del->content))->is_alive == 0 && arena_data->pchain == to_del)
		{
			kill_one_process(to_del, arena_data, 1);
			arena_data->pchain = current;
		}
		else if (((t_process *)(to_del->content))->is_alive == 0 && to_del->next != NULL)
			kill_one_process(to_del, arena_data, 3);
		else
			((t_process *)(to_del->content))->is_alive = 0;
	}
}

/* clean toute la liste
** a la fin du programme
*/

void	clean_list(t_list *begin)
{
	void	(*pf)(void*, size_t);
	
	pf = &free_process;
	ft_lstdel(&begin, pf);
}

/*
** cycle_to_die est appelé à chaque fois que l'on arrive à une fin de cycle
** la fonction remet les compteurs à 0 et augmente le nombre de check_realisé
** cycle_to_die s'occupe également de diminuer le cycle_to_die si besoin
** elle s'occupe egalement de supprimer tous les process mort
*/

static void	cycle_to_die(t_data *arena_data, long *cycle_local)
{
		arena_data->nb_check += 1;
		*cycle_local = 0;
		max_check_live(arena_data);
		arena_data->nb_live = 0;
		kill_dead_process(arena_data);
}

/*
** cycle generale des combats et des regles de corewar
** check_le numero de cycle.
** appele chaque processus pour executer leur action.
** incremente le nombre de cycle à chaque tour de boucle
*/

void	cycle(t_data *arena_data, t_list *process_chain, int verbose)
{
	long cycle_local;

	cycle_local = 0;
	/***************************** TEST *********************************
	t_list *tmp = process_chain;
	((t_process *)(tmp->content))->is_alive = 1;
	tmp = tmp->next;
	((t_process *)(tmp->content))->is_alive = 1;
	tmp = tmp->next;
	((t_process *)(tmp->content))->is_alive = 1;
	tmp = tmp->next;
	((t_process *)(tmp->content))->is_alive = 1;
	****************************** TEST ********************************/
	arena_data->pchain = process_chain;
	if (arena_data->dump == 0)
	{
		ft_hexdump(arena_data->arena, MEM_SIZE);
		clean_list(arena_data->pchain);
		return ;
	}
	while (1)
	{
		cycle_local++;
		arena_data->cycle++;
		if (verbose & VERBOSE_SHOW_CYCLES)
			FP("It is now cycle %llu\n", arena_data->cycle);
		browse_lst(process_chain, arena_data, verbose);
		if (cycle_local == arena_data->cycle_to_die)
			cycle_to_die(arena_data, &cycle_local);
		if (arena_data->nb_process == 0 || arena_data->cycle_to_die <= 0)
			break ;
		if (arena_data->cycle == arena_data->dump)
		{
			ft_hexdump(arena_data->arena, MEM_SIZE);
			break ;
		}
	}
	if (arena_data->nb_process != 0)
		clean_list(arena_data->pchain);
}
