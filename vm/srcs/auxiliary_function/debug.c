/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 08:40:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:32:24 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	show_struct_option(t_option arg_data)
{
	dprintf(1, "\n ┏(＾0＾)┛ COREWAR DEBUG ┗(＾0＾)┓ \n");
	dprintf(1, "\n#ETAT#########STRUCTURE ARGUMENT############\n");
	if (arg_data.dump)
		dprintf(1, "#  le dump devra se faire au tour  : %-3ld   #\n", arg_data.dump);
	else
		dprintf(1, "#  le dump n'est pas à faire       : %-3ld   #\n", arg_data.dump);
	dprintf(1, "#  valeur de la verbose            : %-3hhd   #\n", arg_data.verbose);
	dprintf(1, "#  nombre de champions charge      : %-3d   #\n", arg_data.nb_champ);
	if (arg_data.expected_arg)
		dprintf(1, "#  argument en attente             : %-3d   #\n", (int)arg_data.expected_arg);
	else
		dprintf(1, "#  aucun argument n'est en attente : %-3d   #\n", (int)arg_data.expected_arg);
	dprintf(1, "#  fd des champs :     %3d %3d %3d %3d     #\n", arg_data.fd[0], arg_data.fd[1], arg_data.fd[2], arg_data.fd[3]);
	dprintf(1, "#  num des champs :    %3u %3u %3u %3u     #\n", arg_data.n[0], arg_data.n[1], arg_data.n[2], arg_data.n[3]);
	dprintf(1, "############################################\n\n");
}

void	show_struct_data(t_data arena_data)
{
	dprintf(1, "\n ┏(＾0＾)┛ COREWAR DEBUG ┗(＾0＾)┓ \n");
	dprintf(1, "\n#ETAT#########STRUCTURE DATA****################\n");
	if (arena_data.dump)
		dprintf(1, "#  le dump devra se faire au tour  : % -7ld   #\n", arena_data.dump);
	else
		dprintf(1, "#  le dump n'est pas à faire       : % -7ld   #\n", arena_data.dump);
	dprintf(1, "#  valeur de la verbose            : %- 7hhd   #\n", arena_data.verbose);
	dprintf(1, "#  valeur du cycle en cours        : %- 7lld   #\n", arena_data.cycle);
	dprintf(1, "#  valeur du cycle_to_die          : %- 8d  #\n", arena_data.cycle_to_die);
	dprintf(1, "#  nombre de live                  : %- 7d   #\n", arena_data.nb_live);
	dprintf(1, "#  nombre de checks                : %- 7d   #\n", arena_data.nb_check);
	dprintf(1, "#  nombre de process en vie        : %- 7d   #\n", arena_data.living_process);
	dprintf(1, "#  dernier champions en vie        : %- 7d   #\n", arena_data.last_player_alive);
	dprintf(1, "################################################\n\n");
}

void	tester_1_lst(t_list *begin)
{
	t_list	*elem;
	int		i;

	elem = begin;
	i = 4;
	dprintf(1, "\nProcess num: %d ADRESS CURR %p ADRESS NEXT %p\n", ((t_process *)(elem->content))->id, elem, elem->next);
	dprintf(1, "     test ==> cycle      : %-4d\n", ((t_process *)(elem->content))->cycle);
	dprintf(1, "     test ==> pc         : %-4u | r1  : %x\n", ((t_process *)(elem->content))->pc, ((t_process *)(elem->content))->reg[0]);
	dprintf(1, "     test ==> is_alive   : %-4u | r2  : %x\n", ((t_process *)(elem->content))->is_alive, ((t_process *)(elem->content))->reg[1]);
	dprintf(1, "     test ==> id player  : %-4u | r3  : %x\n", ((t_process *)(elem->content))->id_player, ((t_process *)(elem->content))->reg[2]);
	dprintf(1, "     test ==> carry      : %-4u | r4  : %x\n", ((t_process *)(elem->content))->carry, ((t_process *)(elem->content))->reg[3]);
	if (((t_process *)(elem->content))->opc_curr - 1 >= 0 && ((t_process *)(elem->content))->opc_curr - 1 < 16)
		dprintf(1, "     test ==> instr : %9s | r5  : %x\n", g_op_tab[((t_process *)(elem->content))->opc_curr - 1].name, ((t_process *)(elem->content))->reg[4]);
	else
		dprintf(1, "     test ==> aucune instruct   | r5  : %x\n", ((t_process *)(elem->content))->reg[4]);
	while (++i < 9)
		dprintf(1, "                                | r%d  : %x\n", i + 1, ((t_process *)(elem->content))->reg[i]);
	i--;
	while (++i <= 15)
		dprintf(1, "                                | r%d : %x\n", i + 1, ((t_process *)(elem->content))->reg[i]);
}

void	tester_lst(t_list *elem)
{
	int i;

	dprintf(1, "\n ┏(＾0＾)┛ COREWAR DEBUG ┗(＾0＾)┓ \n");
	dprintf(1, "\n#ETAT#########STRUCTURE PROCESS############\n");
	while (elem)
	{
		tester_1_lst(elem);
		elem = elem->next;
	}
	dprintf(1, "\n##############STRUCTURE PROCESS########FIN#\n");
}

void	print_params_size(t_process *proc, unsigned char ocp)
{
	int i;
	int params_tab[4];

	i = 0;
	while (i < 4)
	{
		params_tab[i] = fill_params_tab(ocp, i);
		i++;
	}
	i = 0;
	FP("======================================================================\n");
	FP("op courante %s size current op = %hhd\n", g_op_tab[proc->opc_curr - 1].name, proc->curr_op_size);
	while (i < 3)
	{
		if (params_tab[i] == 2 && g_op_tab[proc->opc_curr - 1].dir_size == true)
			FP("param[%d] DIR size = %d\n", i, proc->size_params[i]);
		else if (params_tab[i] == 2 && g_op_tab[proc->opc_curr - 1].dir_size == false)
			FP("param[%d] DIR size = %d\n", i, proc->size_params[i]);
		else if (params_tab[i] == 1)
			FP("param[%d] REG size = %d\n", i, proc->size_params[i]);
		else if (params_tab[i] == 3)
			FP("param[%d] IDX size = %d\n", i, proc->size_params[i]);
		i++;
	}
	FP("======================================================================\n");
}
