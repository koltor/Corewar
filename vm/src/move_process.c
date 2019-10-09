/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_process.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 12:00:44 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 16:39:14 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

t_bool	check_opc(int value)
{
	printf("VALUE = %d\n", value);
	if (value >= 0x01 || value <= 0x10)
		return (true);
	return (false);
}

/*
** fais bouger les process et renvoie le nb d'octets bouges, ou -1 si error
*/

long		process_move(t_list *proc, t_data *arena_data)
{
	long ret;

//	ret = 0;
//	opc_curr = arena_data->arena[CVOID->pc]; // a voir 
//	if (check_opc(arena_data->arena[CVOID->pc]))
//		CVOID->pc = (CVOID->pc + curr_op_size) % MEM_SIZE;
//	else
//		CVOID->pc = (CVOID->pc + 1) % MEM_SIZE; // attention a la fin de l arene
	return (0);
}
