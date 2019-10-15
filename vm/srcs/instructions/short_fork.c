/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   short_fork.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:12:19 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 12:26:51 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	short_fork(t_process *proc, t_data *arena_data, int verbose)
{
	char		r[2];
	short		new_link_pc;
	t_process	*fork;
	t_list		*new_link;

	if (!(new_link = ft_lstnew(fork, sizeof(proc))))
		return ;
	ft_bzero(new_link->content, sizeof(proc)); // yes le bzero de la winnnnnnnnnn!!!!!!!!!!!!!!!!!!!!!!!!!
	ft_lstadd(&arena_data->pchain, new_link);
	ft_memmove(&r[0], &arena_data->arena[proc->pc + 1], 1);
	ft_memmove(&r[1], &arena_data->arena[proc->pc + 2], 1);
	new_link_pc = r[1] + r[0];
	ft_memmove(new_link->content, proc, sizeof(proc));
	arena_data->living_process++;
	((t_process *)(new_link->content))->id = ++arena_data->ids_process;
	((t_process *)(new_link->content))->pc = (proc->pc + (new_link_pc % IDX_MOD)) % MEM_SIZE;
	tester_1_lst(arena_data->pchain);
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		dprintf(1, "P%5d | fork %d (%d)\n", proc->id, new_link_pc, ((t_process *)(new_link->content))->pc);
	tester_1_lst(arena_data->pchain);
}
