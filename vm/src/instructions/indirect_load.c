/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   indirect_load.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:11:19 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 17:12:39 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static char	get_ocp_params(char ocp, char params)
{
	const char v[4] = {
		(ocp & 0xc0) >> 6, (ocp & 0x30) >> 4, (ocp & 0xc) >> 2, ocp & 0x3
	};
	return (v[params - 1]);
}

// direct taille 2      OCP 2
// indirect 2           OCP 3
// registre taille 1    OCP 1

static char    process_first_arg(unsigned int pos, char ocp_1, char *arena, short *params)
{
	if (ocp_1 == 1)
	{
		ft_memcpy(params, &arena[pos], 1);
		return (1);
	}
	ft_memcpy(params, &arena[pos], 2);
	*params = short_reverse_octet(*params);
	return (2);
}

static char    process_secon_arg(unsigned int pos, char ocp_1, char *arena, short *params)
{
	if (ocp_1 == 1)
	{
		ft_memcpy(params, &arena[pos], 1);
		return (1);
	}
	ft_memcpy(params, &arena[pos], 2);
	*params = short_reverse_octet(*params);
	return (2);
}

void    indirect_load(t_process *process, t_data *arena_data, int verbose)
{
    char ocp;
    char decalement;
    short params1;
    short params2;
	char r1;

    ft_memcpy(&ocp, &arena_data->arena[process->pc + 1], 1);
    decalement = 2;
    params1 = 0;
    params2 = 0;
    decalement += process_first_arg(process->pc + decalement, get_ocp_params(ocp, 1), arena_data->arena, &params1);
	decalement += process_secon_arg(process->pc + decalement, get_ocp_params(ocp, 2), arena_data->arena, &params2);
	ft_memcpy(&r1, &arena_data->arena[process->pc + decalement], 1);
	process->reg[r1 - 1] = arena_data->arena[((params1 + params2) % IDX_MOD) % MEM_SIZE] & 0x000000ff;
	if (process->reg[r1 - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
	{
		FP("P    %d | ldi %hd %hd r%hhd\n", process->id, params1, params2, r1);
		FP("       | -> load from %hd + %hd = %d (with pc and mod %d)\n", params1, params2,
			(unsigned int)params1 + (unsigned int)params2, (unsigned int)params1 + (unsigned int)params2);
	}
}
