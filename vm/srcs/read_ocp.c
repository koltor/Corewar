/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_ocp.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/08 17:50:15 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 12:49:15 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

char			fill_params_tab(unsigned char ocp, int value)
{
	const unsigned char v[4] = {(ocp & 0xc0) >> 6,
	(ocp & 0x30) >> 4, (ocp & 0xc) >> 2, ocp & 0x3};

	return (v[value]);
}

/*
** split_ocp_analyse repartit les 4 groupes de 2 bits de ocp dans
** les cases de params et les parse en mm temps
** (check que le dernier elem est vide)
*/

static void		split_ocp_analyse(unsigned char params_tab[], unsigned char ocp)
{
	int i;

	i = 0;
	while (i < 4)
	{
		params_tab[i] = fill_params_tab(ocp, i);
		i++;
	}
}

static void		ocp_size_counter(unsigned char params_tab[], t_process *proc)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		if ((params_tab[i] == 2 && g_op_tab[proc->opc_curr - 1].dir_size) ||
			params_tab[i] == 3)
		{
			proc->size_params[i] = 2;
			if (i < g_op_tab[proc->opc_curr - 1].param_count)
				proc->curr_op_size += 2;
		}
		else if (params_tab[i] == 2 && !g_op_tab[proc->opc_curr - 1].dir_size)
		{
			proc->size_params[i] = 4;
			if (i < g_op_tab[proc->opc_curr - 1].param_count)
				proc->curr_op_size += 4;
		}
		else if (params_tab[i] == 1)
		{
			proc->size_params[i] = 1;
			if (i < g_op_tab[proc->opc_curr - 1].param_count)
				proc->curr_op_size += 1;
		}
	}
}

static t_bool	check_valid_ocp(char ocp, char opc)
{
	int		i;
	char	ret;

	i = 1;
	while (i <= g_op_tab[opc - 1].param_count)
	{
		ret = get_param_type(ocp, i);
		ret = (ret == 3) ? 4 : ret;
		if (!(ret & g_op_tab[opc - 1].param_type[i - 1]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void			read_ocp(t_process *proc)
{
	unsigned char ocp;
	unsigned char params_tab[4];

	ocp = proc->ocp_curr;
	proc->valid_ocp = check_valid_ocp(ocp, proc->opc_curr);
	split_ocp_analyse(params_tab, ocp);
	ocp_size_counter(params_tab, proc);
}
