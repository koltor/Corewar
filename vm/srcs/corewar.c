/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   a_corewar.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 11:46:08 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:45:20 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** REMEMBER
** 	ft_hexdump(arena_data.arena, MEM_SIZE); //debug
**	show_struct_option(arg_data);			//debug
**	tester_lst(process_chain);				//debug
**	show_struct_data(t_data arena_data)		//debug
*/

/*
** print_the_winner ecrit le nom du vainqueur
*/

static void	print_the_winner(t_data arena_data)
{
	if (arena_data.last_player_alive == -1)
		FP("Draw !\n");
	else
	{
		FP("Constestant %d, \"%s\", has won !\n",
			arena_data.last_player_alive + 1,
			arena_data.champs_data[arena_data.last_player_alive].prog_name);
	}
}

/*
** dump_zero est une petite fonction au cas ou le dump de memoire
** doit se faire au tour zero
*/

static void	dump_zero(t_data arena_data)
{
	if (arena_data.dump == 0)
	{
		ft_hexdump(arena_data.arena, MEM_SIZE);
		clean_list(arena_data.pchain);
		print_the_winner(arena_data);
		exit(0);
	}
}

/*
** intro_player appele chaque champion pour leur phrase d'introduction
*/

static void	intro_player(t_header dchamps[], unsigned int nb_player)
{
	unsigned int i;

	i = 0;
	FP("Introducing contestants...\n");
	while (i < nb_player)
	{
		FP("* Player %u, weighing %u bytes, \"%s\" (\"%s\") !\n", i + 1,
			dchamps[i].prog_size, dchamps[i].prog_name, dchamps[i].comment);
		i++;
	}
}

/*
** set_arena_data permet de donné des valeurs par default
** à la structure data nommé arena_data
*/

static void	set_arena_data(t_data *arena_data, t_option arg_data)
{
	ft_bzero(arena_data, sizeof(t_data));
	arena_data->dump = arg_data.dump;
	arena_data->verbose = (arg_data.verbose != -1) ? arg_data.verbose : 32;
	arena_data->cycle = 0;
	arena_data->nb_live = 0;
	arena_data->nb_check = 0;
	arena_data->nb_champ = arg_data.nb_champ;
	arena_data->living_process = arg_data.nb_champ;
	arena_data->ids_process = arg_data.nb_champ;
	arena_data->cycle_to_die = CYCLE_TO_DIE;
	arena_data->last_player_alive = -1;
	process_champ(&arg_data, &arena_data->champs_data, arena_data->arena);
	ft_memcpy(&arena_data->n, arg_data.n, sizeof(arg_data.n));
	arena_data->pchain = generate_process_list(arena_data, 0);
}

/*
** le main du programme
*/

int			main(int ac, char **av)
{
	t_data		arena_data;
	t_option	arg_data;

	process_arg(&arg_data, ac - 1, &av[1]);
	set_arena_data(&arena_data, arg_data);
	intro_player(arena_data.champs_data, arg_data.nb_champ);
	dump_zero(arena_data);
	cycle(&arena_data);
	print_the_winner(arena_data);
	return (0);
}
