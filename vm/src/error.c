/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 08:37:24 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 13:53:56 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** invalid_champs indique une erreur au sein du fichier champion
*/

void	invalid_champs(void)
{
	dprintf(1, "champion invalide\n");
	usage();
}

/*
** indique comment utilisé le programme corewar
*/

void	usage(void)
{
	dprintf(1, "usage: ./corewar [-vg] [-d nbr_cycles] [-n number]champion.cor (Max: 4)\n");
	exit(0);
}