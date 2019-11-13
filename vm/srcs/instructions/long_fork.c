/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   long_fork.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:14:13 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 15:08:16 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	long_fork(t_process *proc, t_data *data, int verbose)
{
	t_list *new_link;

	transfer_in_proc(data, proc, 0, ((proc->pc + 1) % MEM_SIZE));
	new_link = copy_process(data, proc, 1);
	ft_lstadd(&(data->pchain), new_link);
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		dprintf(1, "P %4d | lfork %d (%d)\n", proc->id, proc->param[0],
												proc->pc + proc->param[0]);
}
