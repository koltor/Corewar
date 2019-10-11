/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_process.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 14:48:54 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 13:47:45 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	print_params_tab(unsigned char params_tab[], unsigned char ocp)
{
	int i;

	i = 0;
//	FP("ocp en entier %b\n", ocp);
	while (i < 4)
	{
//		FP("params_tab[%d] aff binaire %b\n", i, params_tab[i]);
		i++;
	}
}

static char				fill_params_tab(unsigned char ocp, int value)
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
	print_params_tab(params_tab, ocp);
}

static void				ocp_size_counter(unsigned char params_tab[], t_process *proc, unsigned char ocp)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (params_tab[i] == 2 && op_tab[proc->opc_curr - 1].dir_size == true)
		{
//			FP("DIR2\n");
			proc->curr_op_size += 2;
		}
		else if (params_tab[i] == 2 && op_tab[proc->opc_curr - 1].dir_size == false)
		{
//			FP("DIR4\n");
			proc->curr_op_size += 4;
		}
		else if (params_tab[i] == 1)
		{
//			FP("REG1\n");
			proc->curr_op_size += 1;
		}
		else if (params_tab[i] == 3)
		{
//			FP("IDX2\n");
			proc->curr_op_size +=2;
		}
		i++;
	}
}

static void				read_ocp(t_process *proc, t_data *arena_data)
{
	unsigned char 	ocp;
	unsigned char 	params_tab[4];
	int				test;

	ft_bzero(params_tab, 4); // does this work??
	ocp = arena_data->arena[proc->pc + 1];
	proc->ocp_cr = ocp;
	split_ocp_analyse(params_tab, proc, ocp);
	ocp_size_counter(params_tab, proc, ocp);
}

/*
** fais bouger les process et renvoie le nb d'octets bouges, ou -1 si error
*/

static void				get_op_size(t_process *proc, t_data *arena_data)
{
	if (proc->opc_curr == 0xF || proc->opc_curr == 0xC || proc->opc_curr == 0x9 || proc->opc_curr == 0x10)
		proc->curr_op_size = 3;
	else if (proc->opc_curr == 0x04 || proc->opc_curr == 0x05 || proc->opc_curr == 0x01)
		proc->curr_op_size = 5;
	else
	{
		proc->curr_op_size += 2;
		read_ocp(proc, arena_data);
	}
}

void					get_mem(t_process *proc, t_data *arena_data, char *mem)
{
	int i;
	int j;
	int k;

	k = 0;
	i = proc->curr_op_size;
	j = (proc->opc_curr == 0xF || proc->opc_curr == 0xC || proc->opc_curr == 0x9 || proc->opc_curr == 0x10) ? 1 : 2;
	while (i--)
	{
		k = ft_sprintf(&mem[k], "%02hhx", arena_data->arena[proc->pc + j]);
		if (i != 1)
			k = k + 1;
		j++;
	}
	//ft_sprintf(&mem[i * 3], "%hhx", arena_data->arena[proc->pc + j]);
}

int						process_move(t_process *proc, t_data *arena_data, int verbose)
{
	int old_pc;
	char *mem;

	mem = "          ";
	proc->curr_op_size = 0;
	if (proc->to_move == true) // op qui est passe dans le t de pf
	{

		get_op_size(proc, arena_data);
		if (proc->opc_curr == 0x9)
		{
			proc->opc_curr = arena_data->arena[proc->pc];
			proc->cycle = op_tab[proc->opc_curr - 1].cycles;
			return (0);
		}
		old_pc = proc->pc;
		proc->pc = (proc->pc + proc->curr_op_size) % MEM_SIZE;
		proc->to_move = false;
		proc->opc_curr = arena_data->arena[proc->pc];
		proc->cycle = op_tab[proc->opc_curr - 1].cycles;
		if (verbose & VERBOSE_SHOW_PC_MOVEMENTS)
		{
			mem = ft_strnew(20);
			get_mem(proc, arena_data, mem);
			FP("AVD %hhd (0x%x -> 0x%x) %s\n", proc->curr_op_size, old_pc, proc->pc, mem);
		}
	}
	else if (arena_data->arena[proc->pc] == 0)
	{
		proc->pc = (proc->pc + 1) % MEM_SIZE;
		if (arena_data->arena[proc->pc] >= 0x01 && arena_data->arena[proc->pc] <= 0x10)
			proc->opc_curr = arena_data->arena[proc->pc];
	}
	return (0);
}
