/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   j_clean_process.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 15:00:19 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 12:57:34 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** free_process libere la memoire de 1 proccess
** en faisant appel à ft_memdel
*/

static void		free_process(void *data, size_t data_size)
{
	(void)data_size;
	ft_memdel(&data);
}

/*
** get_prev est une sous_fonction necessaire à kill_one_process pour son
** fonctionnement
*/

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
** la liste des process due à la suppression de ce dernier
** bv 1 : cas de suppression du premier process de la liste
** bv 2 : cas du dernier elément
** bv 3 : cas d'un process intermerdiaire
*/

static void		kill_one_process(t_list *elem, t_data *arena_data, int bv)
{
	void	(*pf)(void*, size_t);
	t_list	*prev;
	t_list	*begin;

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
	arena_data->living_process--;
	if (arena_data->living_process == 0)
		arena_data->pchain = NULL;
	else if (arena_data->living_process == 1)
		(arena_data->pchain)->next = NULL;
}

/*
** libere la memoire prise par la liste des process
** a appeler à la fin du programme
*/

void			clean_list(t_list *begin)
{
	void	(*pf)(void*, size_t);

	pf = &free_process;
	ft_lstdel(&begin, pf);
}

/*
** boucle dans la chaine de process et supprime les process
** ou leur valeur 'is_alive' est set à zero
*/

void			kill_dead_process(t_data *arena_data)
{
	t_list		*current;
	t_list		*to_del;
	t_process	*process;

	current = arena_data->pchain;
	while (current)
	{
		to_del = current;
		current = current->next;
		process = (t_process *)(to_del->content);
		if (process->is_alive == 0 && arena_data->pchain == to_del)
		{
			kill_one_process(to_del, arena_data, 1);
			arena_data->pchain = current;
		}
		else if (process->is_alive == 0 && to_del->next != NULL)
			kill_one_process(to_del, arena_data, 3);
		else
			process->is_alive = 0;
	}
}
