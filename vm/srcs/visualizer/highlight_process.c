/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   highlight_process.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/25 17:57:00 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 13:34:45 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

static int	get_rect_width(t_process *process, int width)
{
	int		cycle_ref;
	double	pourcent;

	if (process->opc_curr <= 0x00 || process->opc_curr >= 0x10)
		return (width);
	cycle_ref = g_op_tab[process->opc_curr - 1].cycles;
	pourcent = (double)process->cycle / (double)cycle_ref;
	if (pourcent > 0.98)
		pourcent = 0;
	return (width * (1 - pourcent));
}

void		highlight_process(t_data *data)
{
	t_list		*begin;
	t_env		*env;
	SDL_Rect	*rect;
	int			i;

	begin = data->pchain;
	env = g_env(NULL);
	i = -1;
	while (++i < 128 && begin)
	{
		rect = &env->arena.rect[((t_process*)(begin->content))->pc];
		rect->w = get_rect_width(((t_process*)(begin->content)), rect->w);
		if (((t_process*)(begin->content))->is_alive)
			SDL_FillRect(env->screen, rect, 0xffffff);
		else
			SDL_FillRect(env->screen, rect, 0xaaaaaa);
		rect->w = env->arena.square_size_x;
		begin = begin->next;
	}
}
