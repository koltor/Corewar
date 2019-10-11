/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generate_start_process.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 15:11:34 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 11:59:28 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

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

static void	get_cycle_instr(t_process *process, char *arena)
{
	process->opc_curr = arena[process->pc];
	process->cycle = op_tab[process->opc_curr - 1 ].cycles;
}

/*
** genere une liste de process en fonction du nb de champions passé
** en parametres
*/

t_list		*generate_process_list(t_option arg_data, char *arena)
{
	t_list		*begin;
	t_list		*tmp;
	int			i;
	t_process	proc;

	i = 1;
	ft_bzero(&proc, sizeof(proc));
	if (!(begin = ft_lstnew(&proc, sizeof(proc))))
		free_proccess_list_in_case_of_error(begin);
	/***************TEST*********************/
//	((t_process *)(begin->content))->carry = 1;
	((t_process *)(begin->content))->id_player = 0;
	((t_process *)(begin->content))->reg[0] = arg_data.n[0];
	((t_process *)(begin->content))->id = 1;
	((t_process *)(begin->content))->pc = get_pc(arg_data.nb_champ, 0);
//	((t_process *)(begin->content))->opc = get_op_number(arg_data.nb_champ, 0);
	get_cycle_instr(((t_process *)(begin->content)), arena);
	while (i < arg_data.nb_champ)
	{
		if (!(tmp = ft_lstnew(&proc, sizeof(proc))))
			free_proccess_list_in_case_of_error(begin);
		ft_lstadd(&begin, tmp);
		((t_process *)(tmp->content))->id_player = i;
		((t_process *)(tmp->content))->id = i + 1;
		/***************TEST*********************/
//		((t_process *)(tmp->content))->carry = 1;
		((t_process *)(begin->content))->pc = get_pc(arg_data.nb_champ, i);
		get_cycle_instr(((t_process *)(begin->content)), arena);
		i++;
	}
	return (begin);
}
