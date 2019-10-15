/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   long_fork.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:14:13 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 12:13:46 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	long_fork(t_process *proc, t_data *arena_data, int verbose)
{
	char		r[2];
	short		new_link_pc;
	t_process	*fork;
	t_list		*new_link;

	if (!(new_link = ft_lstnew(fork, sizeof(proc))))
		return ;
	ft_bzero(new_link->content, sizeof(proc)); // yes le bzero de la winnnnnnnnnn!!!!!!!!!!!!!!!!!!!!!!!!!
	ft_lstadd(&arena_data->pchain, new_link);
	ft_memmove(&new_link_pc, &arena_data->arena[proc->pc + 1], 2);
	new_link_pc = short_reverse_octet(new_link_pc);
	ft_memmove(new_link->content, proc, sizeof(proc));
	arena_data->living_process++;
	((t_process *)(new_link->content))->id = ++arena_data->ids_process;
	((t_process *)(new_link->content))->pc = (proc->pc + (new_link_pc % IDX_MOD)) % MEM_SIZE;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		FP("P%5d | lfork %d (%d)\n", proc->id, new_link_pc, ((t_process *)(new_link->content))->pc);
}
