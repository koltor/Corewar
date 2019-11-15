/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   direct_load.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:03:23 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 17:09:51 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int	pr_indirect(char n, char *dclm_pc, t_process *process, t_data *data)
{
	int val;

	if (n != 1)
	{
		*dclm_pc = 0;
		return (0);
	}
	val = 0;
	ft_memcpy_memsize(&val, &data->arena, process->pc + *dclm_pc, 2);
	val = (short)unsigned_short_reverse_octet((unsigned short)val);
	val = val % IDX_MOD;
	ft_memcpy_memsize(&val, &data->arena, (process->pc + val) % MEM_SIZE, 4);
	val = (int)unsigned_int_reverse_octet((unsigned int)val);
	*dclm_pc += 2;
	return (val);
}

static int	pr_direct(char n, char *dclm_pc, t_process *process, t_data *data)
{
	int val;

	if (n != 1)
	{
		*dclm_pc = 0;
		return (0);
	}
	val = 0;
	ft_memcpy_memsize(&val, &data->arena, process->pc + *dclm_pc, 4);
	val = (int)unsigned_int_reverse_octet((unsigned int)val);
	*dclm_pc += 4;
	return (val);
}

static int	pr_registre(char n, char *dclm_pc, t_process *process, t_data *data)
{
	int val;

	val = 0;
	ft_memcpy_memsize(&val, &data->arena, process->pc + *dclm_pc, 1);
	if (n != 2 || val <= 0 || val >= 17)
	{
		*dclm_pc = 0;
		return (0);
	}
	return (val);
}

void		direct_load(t_process *process, t_data *data, int verbose)
{
	char			ocp;
	char			r1;
	char			dclm_pc;
	int				val;
	static int		(*f[3])(char, char*, t_process*, t_data*) = {
		&pr_registre, &pr_direct, &pr_indirect
	};

	dclm_pc = 1;
	ocp = process->ocp_curr;
	dclm_pc += 1;
	val = f[get_param_type(ocp, 1) - 1](1, &dclm_pc, process, data);
	if (dclm_pc == 0)
		return ;
	r1 = (char)f[get_param_type(ocp, 2) - 1](2, &dclm_pc, process, data);
	if (dclm_pc == 0)
		return ;
	process->reg[r1 - 1] = val;
	process->carry = (val == 0) ? 1 : 0;
	if (verbose & VERBOSE_SHOW_OPERATIONS)
		ft_printf("P %4d | ld %d r%hhd\n", process->id, val, r1);
}
