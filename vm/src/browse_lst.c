/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   browse_lst.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 11:55:14 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 16:35:23 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
**
**
**
*/

static void		*get_funtion_to_execute(int value)
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

	if (value >= 0x01 || value <= 0x10)
		return (p[value - 1]);
	return (NULL);
}

/*
** exec_instruc  est appelé lors de l'execution d'une instruction
*/

static void		exec_instr(t_process *process, t_data *arena_data, int verbose)
{
	void (*f)(t_process*, t_data*, int);

	f = get_funtion_to_execute(process->opc_curr);
	if (f != NULL)
		f(process, arena_data, verbose);
}

int				browse_lst(t_list *begin, t_data *arena_data, int verbose)
{
	int 	ret;

	ret = 0;
	begin = arena_data->pchain;
	while (begin)
	{
		((t_process *)(begin->content))->cycle--;
		if (((t_process *)(begin->content))->cycle == 0)
		{
			exec_instr(begin->content, arena_data, verbose);
		//	tester_1_lst(begin);
			process_move(begin, arena_data);
			ret++;
		}
		begin = begin->next;
	}
	return (ret);
}
