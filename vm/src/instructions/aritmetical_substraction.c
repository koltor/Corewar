/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aritmetical_substraction.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 11:07:39 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 13:45:53 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void    aritmetical_substraction(t_process *process, t_data *arena_data, int verbose)
{
    char ocp;
    char r1;
    char r2;
    char r3;

    ft_memcpy(&ocp, &arena_data->arena[process->pc + 1], 1);
    ft_memcpy(&r1, &arena_data->arena[process->pc + 2], 1);
    ft_memcpy(&r2, &arena_data->arena[process->pc + 3], 1);
    ft_memcpy(&r3, &arena_data->arena[process->pc + 4], 1);
    if (r1 <= 0 || r2 <= 0 || r3 <= 0 || r1 >= 17 || r2 >= 17 || r3 >= 17) // comportement indeterminer
        return ;
    process->reg[r3 - 1] = process->reg[r1 - 1] - process->reg[r2 - 1];
    if (process->reg[r3 - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    if (verbose & VERBOSE_SHOW_OPERATIONS)
        FP("P    %d | sub r%hhd r%hhd r%hhd\n", process->id, r1, r2, r3);
}
