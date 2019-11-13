/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   interface.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 18:19:52 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 09:47:57 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void	print_variable(t_data *data, unsigned long cycle_local)
{
	t_env			*env;
	SDL_Rect		rect;
	TTF_Font		*fz;

	env = g_env(NULL);
	fz = env->police1;
	rect.x = env->win_size.x - (env->win_size.x / 18) * 2;
	rect.y = 5;
	rect.h = env->win_size.y / 25;
	rect.w = env->win_size.x / 28;
	print_value(data->cycle, &rect, (SDL_Color){150, 150, 150, 0}, fz);
	rect.y = 5 + rect.h;
	rect.x = env->win_size.x - (env->win_size.x / 5) + 10;
	rect.w = env->win_size.x / 5 - 20;
	draw_empty_rect(&rect, 15784682, 2);
	rect.w = rect.w * ((double)cycle_local / (double)data->cycle_to_die);
	SDL_FillRect(env->screen, &rect, 1578464);
	rect.w = rect.w * (((double)data->nb_check + 1) / (double)MAX_CHECKS);
	SDL_FillRect(env->screen, &rect, 1578465874);
	rect.x = env->win_size.x - (env->win_size.x / 18) * 2;
	rect.w = env->win_size.x / 28;
	rect.y = 5 + rect.h;
	print_value(data->cycle_to_die, &rect, (SDL_Color){175, 175, 175, 0}, fz);
	rect.y += 5 + rect.h;
	print_value(data->living_process, &rect, (SDL_Color){175, 100, 100, 0}, fz);
}

void	visu_interface(t_data *data, unsigned long cycle_local)
{
	live_bar(data);
	print_variable(data, cycle_local);
}
