/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   long_fork.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:14:13 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 17:09:51 by matheme     ###    #+. /#+    ###.fr     */
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
		ft_printf("P %4d | lfork %d (%d)\n", proc->id, proc->param[0],
												proc->pc + proc->param[0]);
}
