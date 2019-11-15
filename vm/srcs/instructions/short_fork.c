/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   short_fork.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:12:19 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 17:09:51 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		get_cycle_forks(int opc_value)
{
	if (opc_value <= 0x10 && opc_value >= 0x01)
		return (g_op_tab[opc_value - 1].cycles);
	return (0);
}

t_list	*copy_process(t_data *data, t_process *proc, int bv)
{
	int			pc;
	t_process	fork;
	t_list		*new_link;

	ft_bzero(&fork, sizeof(t_process));
	if (!(new_link = ft_lstnew(&fork, sizeof(t_process))))
	{
		f_error(0);
		return (NULL);
	}
	ft_memmove(new_link->content, proc, sizeof(t_process));
	pc = (bv == 0) ? (proc->pc + (proc->param[0] % IDX_MOD)) % MEM_SIZE :
						(proc->pc + proc->param[0]) % MEM_SIZE;
	if (pc < 0)
		pc = MEM_SIZE - pc;
	((t_process *)(new_link->content))->pc = pc;
	data->living_process++;
	data->ids_process++;
	((t_process *)(new_link->content))->id = data->ids_process;
	((t_process *)(new_link->content))->opc_curr = data->arena[pc];
	((t_process *)(new_link->content))->ocp_curr =
				data->arena[(pc + 1) % MEM_SIZE];
	return (new_link);
}

void	short_fork(t_process *proc, t_data *data, int verbose)
{
	t_list	*new_link;

	transfer_in_proc(data, proc, 0, ((proc->pc + 1) % MEM_SIZE));
	new_link = copy_process(data, proc, 0);
	ft_lstadd(&(data->pchain), new_link);
	if (verbose & VERBOSE_SHOW_OPERATIONS)
	{
		ft_printf("P %4d | fork %d (%d)\n", proc->id, proc->param[0],
								proc->pc + (proc->param[0] % IDX_MOD));
	}
}
