/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 08:37:24 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 12:36:33 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** indique comment utilisé le programme corewar
*/

void		usage(void)
{
	FP("usage: ./corewar [-vg] [-d nbr_cycles][-n number]\
champion.cor (Max: 4)\n");
	if (errno)
		ft_printf("==> %s\n", strerror(errno));
	exit(0);
}

/*
** fonction de gestion des erreurs
*/

static void	ft_strerror(int err_nb)
{
	const char *tab[] = {
		"malloc crashed\n", "a file is not a corewar_champs\n",
		"a corewar_champs is too big\n", "a corewar_champs is corrupt\n"
	};

	ft_putstr(tab[err_nb]);
}

void		f_error(int err_nb)
{
	ft_strerror(err_nb);
	exit(0);
}
