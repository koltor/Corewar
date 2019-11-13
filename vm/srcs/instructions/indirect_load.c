/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   indirect_load.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:11:19 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 13:57:25 by kgrosjea    ###    #+. /#+    ###.fr     */
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

	if (n == 3)
	{
		*dclm_pc = 0;
		return (0);
	}
	val = 0;
	ft_memcpy_memsize(&val, &data->arena, process->pc + *dclm_pc, 2);
	val = (short)unsigned_short_reverse_octet((unsigned short)val);
	*dclm_pc += 2;
	return (val);
}

static int	pr_registre(char n, char *dclm_pc, t_process *process, t_data *data)
{
	int val;

	val = 0;
	ft_memcpy_memsize(&val, &data->arena, process->pc + *dclm_pc, 1);
	if (val <= 0 || val >= 17)
	{
		*dclm_pc = 0;
		return (0);
	}
	*dclm_pc += 1;
	if (n == 3)
		return (val);
	return (process->reg[val - 1]);
}

static void	print_verbose(int verbose, t_process *proc, int val[3], char r1)
{
	if (verbose & VERBOSE_SHOW_OPERATIONS)
	{
		dprintf(1, "P %4d | ldi %d %d r%hhd\n", proc->id, val[0], val[1], r1);
		print_space_for_indirect(proc->id);
		dprintf(1, "| -> load from %d + %d = %d (with pc and mod %d)\n", val[0],
		val[1], val[0] + val[1],
		(int)(proc->pc + ((val[0] + val[1]) % IDX_MOD)) % MEM_SIZE);
	}
}

void		indirect_load(t_process *process, t_data *data, int verbose)
{
	char			ocp;
	char			r1;
	char			dclm_pc;
	int				val[3];
	static int		(*f[3])(char, char*, t_process*, t_data*) = {
		&pr_registre, &pr_direct, &pr_indirect
	};

	dclm_pc = 1;
	ocp = process->ocp_curr;
	dclm_pc += 1;
	val[0] = f[get_param_type(ocp, 1) - 1](1, &dclm_pc, process, data);
	if (dclm_pc != 0)
		val[1] = f[get_param_type(ocp, 2) - 1](2, &dclm_pc, process, data);
	if (dclm_pc != 0)
		r1 = (char)f[get_param_type(ocp, 3) - 1](3, &dclm_pc, process, data);
	if (dclm_pc == 0)
		return ;
	ft_memcpy_memsize(&val[2], &data->arena,
				(process->pc + ((val[0] + val[1]) % IDX_MOD)) % MEM_SIZE, 4);
	val[2] = unsigned_int_reverse_octet(val[2]);
	process->carry = (val[2] == 0) ? 1 : 0;
	process->reg[r1 - 1] = val[2];
	print_verbose(verbose, process, val, r1);
}
