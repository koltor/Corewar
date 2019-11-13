/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generate_start_process.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 15:11:34 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 13:34:45 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** free_proccess_list_in_case_of_error permet de liberer la memoire en cas
** d'erreur lors de la generation de la chaine de process
** arrete le programme instantanément !
*/

static void	free_proccess_list_in_case_of_error(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		free(list->content);
		tmp = list->next;
		free(list);
		list = tmp;
	}
	f_error(ERR_MALLOC);
}

/*
** get_pc permet de recuperer la position initial du process appelant
** cela depend du nombre de champion
*/

static int	get_pc(int nb_champs, int n_champ)
{
	float	section;
	int		i;

	if (nb_champs != 0)
		section = MEM_SIZE / nb_champs;
	else
		section = MEM_SIZE;
	if (section - (int)section > 0.5)
		section = section + 1.0;
	i = n_champ * (int)section;
	return (i);
}

/*
** generate_process_list genere les premiers process
** de chaque champion sous forme de liste chainé
** la fonction renvoie le debut de la liste
*/

void		generate_process_list(t_data *data, int i)
{
	t_list		*begin;
	t_list		*tmp;
	t_process	proc;

	i = 0;
	ft_bzero(&proc, sizeof(t_process));
	if (!(begin = ft_lstnew(&proc, sizeof(t_process))))
		free_proccess_list_in_case_of_error(begin);
	((t_process *)(begin->content))->id_player = 0;
	((t_process *)(begin->content))->reg[0] = data->n[0];
	((t_process *)(begin->content))->id = 1;
	((t_process *)(begin->content))->pc = get_pc(data->nb_champ, 0);
	while (++i < data->nb_champ)
	{
		ft_bzero(&proc, sizeof(t_process));
		if (!(tmp = ft_lstnew(&proc, sizeof(t_process))))
			free_proccess_list_in_case_of_error(begin);
		ft_lstadd(&begin, tmp);
		((t_process *)(tmp->content))->id_player = i;
		((t_process *)(tmp->content))->reg[0] = data->n[i];
		((t_process *)(tmp->content))->id = i + 1;
		((t_process *)(tmp->content))->pc = get_pc(data->nb_champ, i);
	}
	data->pchain = begin;
}
