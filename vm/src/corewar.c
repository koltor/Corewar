/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 11:46:08 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 11:33:43 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** cycle Generale de la partie
*/

void	cycle(void)
{
	
}

/*
** generate_process permet de generer les premier processus de chaque champion
*/

void	generate_process(void)
{
	t_process	process;

	ft_bzero(&process, sizeof(process));
}

/*
** le main du programme
*/

int		main(int ac, char **av)
{
	t_data		arena_data;
	t_option	arg_data;
	t_header	champs_data[MAX_PLAYERS];

	ft_bzero(&arena_data, sizeof(arena_data));
	ft_bzero(&arg_data, sizeof(arg_data));
	ft_bzero(&champs_data, sizeof(champs_data));
	process_arg(&arg_data, ac - 1, &av[1]);
	process_champ(arg_data, &champs_data, arena_data.arena);
	hexdump(arena_data.arena, MEM_SIZE);
	generate_process();
	cycle();
	return (0);
}
