/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 08:40:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/30 08:41:00 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	show_struct_option(t_option arg_data)
{
	dprintf(1, "dump = %d\n", arg_data.dump);
	dprintf(1, "option = %d\n", arg_data.option);
	dprintf(1, "champs = %d\n", arg_data.nb_champ);
	dprintf(1, "expected_arg = %d\n", (int)arg_data.expected_arg);
	dprintf(1, "%d %d %d %d\n", arg_data.fd[0], arg_data.fd[1], arg_data.fd[2], arg_data.fd[3]);
	dprintf(1, "%d %d %d %d\n", arg_data.n[0], arg_data.n[1], arg_data.n[2], arg_data.n[3]);
}
