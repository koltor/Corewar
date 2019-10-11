/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   browse_lst.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 11:55:14 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 13:49:57 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void		*get_funtion_to_execute(t_process *process)
{
	static void	(*p[16])(t_process*, t_data*, int) = {
		&live,
		&direct_load,
		&direct_store,
		&aritmetical_addition,
		&aritmetical_substraction,
		&logical_and,
		&logical_or,
		&logical_xor,
		&jump_if_zero,
		&indirect_load,
		&indirect_store,
		&short_fork,
		&long_direct_load,
		&long_indirect_load,
		&long_fork,
		&aff
	};

	if (process->opc_curr >= 0x01 || process->opc_curr <= 0x10)
	{
		return (p[process->opc_curr - 1]);
	}
	return (NULL);
}

/*
** exec_instruc est appelé lors de l'execution d'une instruction
*/

static void		exec_instr(t_process *process, t_data *arena_data, int verbose)
{
	void (*f)(t_process*, t_data*, int);

	f = get_funtion_to_execute(process);
	if (f != NULL)
	{
		process->to_move = true;
		f(process, arena_data, verbose);
	}
}

void			browse_lst(t_list *begin, t_data *arena_data, int verbose)
{
	begin = arena_data->pchain;
	while (begin)
	{
		((t_process *)(begin->content))->cycle--;
		if (((t_process *)(begin->content))->cycle == 0)
		{
			exec_instr(begin->content, arena_data, verbose);
			process_move(begin->content, arena_data, verbose);
		}
		begin = begin->next;
	}
}
