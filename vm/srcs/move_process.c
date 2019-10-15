/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   i_move_process.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 14:48:54 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 13:00:11 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"


char					fill_params_tab(unsigned char ocp, int value)
{
	const unsigned char v[4] = {(ocp & 0xc0) >> 6, (ocp & 0x30) >> 4, (ocp & 0xc) >> 2, ocp & 0x3};

	return (v[value]);
}

static void				parse_params_tab(unsigned char params_tab[], t_process *proc)
{
	if (params_tab[3] != 0)
	{
		proc->valid_ocp = false;
//		FP("OCP corrompu\n");
		return ;
	}
	if ((proc->opc_curr == 0x2 || proc->opc_curr == 0x3 || proc->opc_curr == 0xd) && params_tab[0] != 0)
	{
//		FP("instructions a 2 params qui en ont 3\n");
		proc->valid_ocp = false;
		return ;
	}
	else if ((proc->opc_curr == 0x6 || proc->opc_curr == 0x7 || proc->opc_curr == 0x8 || proc->opc_curr == 0xa || proc->opc_curr == 0xb || proc->opc_curr == 0xe) && (params_tab[0] == 0 || params_tab[1] == 0 || params_tab[2] == 0))
	{
		proc->valid_ocp = false;
//		FP("instructions a 3 params qui en ont enter 0 et 2\n");
		return ;
	}
	proc->valid_ocp = true;
}

/*
** split_ocp_analyse repartit les 4 groupes de 2 bits de ocp dans
** les cases de params et les parse en mm temps (check que le dernier elem est vide)
*/


static void				split_ocp_analyse(unsigned char params_tab[], t_process *proc, unsigned char ocp)
{
	int i;


	i = 0;
	while (i < 4)
	{
		params_tab[i] = fill_params_tab(ocp, i);
		i++;
	}
	parse_params_tab(params_tab, proc);
	//print_params_tab(params_tab, ocp);
}


static void				ocp_size_counter(unsigned char params_tab[], t_process *proc, unsigned char ocp)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (params_tab[i] == 2 && g_op_tab[proc->opc_curr - 1].dir_size == true)
		{
	//		FP("DIR2\n");
			proc->size_params[i] = 2;
			proc->curr_op_size += 2;
		}
		else if (params_tab[i] == 2 && g_op_tab[proc->opc_curr - 1].dir_size == false)
		{
	//		FP("DIR4\n");
			proc->size_params[i] = 4;
			proc->curr_op_size += 4;
		}
		else if (params_tab[i] == 1)
		{
	//		FP("REG1\n");
			proc->size_params[i] = 1;
			proc->curr_op_size += 1;
		}
		else if (params_tab[i] == 3)
		{
	//		FP("IDX2\n");
			proc->size_params[i] = 3;
			proc->curr_op_size +=2;
		}
		i++;
	}
}

int testg = 0;
void				read_ocp(t_process *proc, t_data *arena_data)
{
	unsigned char 	ocp;
	unsigned char 	params_tab[4];
	int				test;

	ft_bzero(params_tab, 4); // does this work??
	ft_bzero(proc->size_params, 3); // does this work??
	ocp = arena_data->arena[proc->pc + 1];
	split_ocp_analyse(params_tab, proc, ocp);
	ocp_size_counter(params_tab, proc, ocp);
//	FP("\n*************************************************************************\npassage %d dans read ocp || ocp curr bin %b || size op %u\n", ++testg, proc->ocp_cr, proc->curr_op_size);

}

/*
** fait bouger les process et renvoie le nb d'octets bouges, ou -1 si error
*/

void				get_op_size(t_process *proc, t_data *arena_data)
{
//	FP("HEELOOOOO GET OP SIZE\n");
	if (proc->opc_curr == 0xF || proc->opc_curr == 0xC || proc->opc_curr == 0x9 || proc->opc_curr == 0x10)
	{
		proc->size_params[0] = 1;
		proc->size_params[1] = 1;
		proc->curr_op_size = 3;
	}
	else if (proc->opc_curr == 0x04 || proc->opc_curr == 0x05 || proc->opc_curr == 0x01)
	{
		proc->size_params[0] = 2;
		proc->size_params[1] = 2;
		proc->curr_op_size = 5;
	}
	else
	{
		proc->curr_op_size += 2;
		read_ocp(proc, arena_data);
	}
}

void					print_mem(t_process *proc, t_data *arena_data, int old_pc)
{
	int i;

	i = 0;
	while (i < proc->curr_op_size)
	{
		if (i != proc->curr_op_size - 1)
			FP("%02hhx ", arena_data->arena[old_pc]);
		else
			FP("%02hhx \n", arena_data->arena[old_pc]);
		i++;
		old_pc++;
	}
}

int						process_move(t_process *proc, t_data *arena_data, int verbose)
{
	int old_pc;
	
	proc->curr_op_size = 0;
	if (proc->to_move == true) // op qui est passe dans le t de pf
	{

		get_op_size(proc, arena_data);
		if (proc->opc_curr == 0x9)
		{
			proc->opc_curr = arena_data->arena[proc->pc];
			proc->cycle = g_op_tab[proc->opc_curr - 1].cycles;
			return (0);
		}
		old_pc = proc->pc;
		proc->pc = (proc->pc + proc->curr_op_size) % MEM_SIZE;
		proc->to_move = false;
		proc->opc_curr = arena_data->arena[proc->pc];
		proc->cycle = g_op_tab[proc->opc_curr - 1].cycles;
		if (verbose & VERBOSE_SHOW_PC_MOVEMENTS)
		{
			FP("ADV %hhd (0x%.4x -> 0x%.4x) ", proc->curr_op_size, old_pc, proc->pc);
			print_mem(proc, arena_data, old_pc);
		}
	}
	else if (arena_data->arena[proc->pc] == 0)
	{
		proc->pc = (proc->pc + 1) % MEM_SIZE;
		if (arena_data->arena[proc->pc] >= 0x01 && arena_data->arena[proc->pc] <= 0x10)
			proc->opc_curr = arena_data->arena[proc->pc];
	}
	if (arena_data->arena[proc->pc] != 0)
		get_op_size(proc, arena_data);
	return (0);
}
