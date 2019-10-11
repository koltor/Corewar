/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 11:46:08 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 13:44:15 by matheme     ###    #+. /#+    ###.fr     */
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

static void	introducing_player(t_header champs_data[MAX_PLAYERS], unsigned int nb_player)
{
	unsigned int i;

	i = 0;
	FP("Introducing contestants...\n");
	while (i < nb_player)
	{
		FP("* Player %u, weighing %u bytes, \"%s\" (\"%s\") !\n",
			i + 1,
			champs_data[i].prog_size,
			champs_data[i].prog_name,
			champs_data[i].comment);
		i++;
	}
}

void	print_the_winner(t_data arena_data)
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

static void	set_arena_data(t_data *arena_data, t_option arg_data)
{
	arena_data->dump = arg_data.dump;
	arena_data->verbose = (arg_data.verbose != -1) ? arg_data.verbose : 32;
	arena_data->cycle = 0;
	arena_data->cycle_to_die = CYCLE_TO_DIE;
	arena_data->nb_live = 0;
	arena_data->nb_check = 0;
	arena_data->nb_process = arg_data.nb_champ;
	arena_data->last_player_alive = -1;
	ft_memcpy(&arena_data->n, arg_data.n, sizeof(arg_data.n));
}

/*
** le main du programme
*/

int		main(int ac, char **av)
{
	t_data		arena_data;
	t_option	arg_data;
	t_list		*process_chain;

	ft_bzero(&arena_data, sizeof(arena_data));
	ft_bzero(&arg_data, sizeof(arg_data));
	process_arg(&arg_data, ac - 1, &av[1]);
	process_champ(&arg_data, &arena_data.champs_data, arena_data.arena);
	process_chain = generate_process_list(arg_data, arena_data.arena);
	set_arena_data(&arena_data, arg_data);
	introducing_player(arena_data.champs_data, arg_data.nb_champ);
	cycle(&arena_data, process_chain, arena_data.verbose);
	print_the_winner(arena_data);
	return (0);
}
