/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   h_browse_process.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 11:55:14 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 12:46:12 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** get_funtion_to_execute contient toute les fonctions des insctructions
** revoie l'adresse de la bonne fonction à appeler
*/

static void		*get_funtion_to_execute(unsigned char opc_curr)
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

	if (opc_curr >= 0x01 || opc_curr <= 0x10)
		return (p[opc_curr - 1]);
	return (NULL);
}

/*
** exec_instruc permet d'executer l'instruction inscrite dans le process
** appelant
*/

static void		exec_instr(t_process *process, t_data *arena_data)
{
	void (*f)(t_process*, t_data*, int);

	f = get_funtion_to_execute(process->opc_curr);
	if (f != NULL)
	{
		process->to_move = true;
		f(process, arena_data, arena_data->verbose);
	}
}

void			browse_process(t_data *arena_data)
{
	t_list *begin;

	begin = arena_data->pchain;
	while (begin)
	{
		if (((t_process *)(begin->content))->cycle != 0)
			((t_process *)(begin->content))->cycle--;
		if (((t_process *)(begin->content))->cycle == 0)
		{
			exec_instr(begin->content, arena_data);
			process_move(begin->content, arena_data, arena_data->verbose);
		}
		begin = begin->next;
	}
}
