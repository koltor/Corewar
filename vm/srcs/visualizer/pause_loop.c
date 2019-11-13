/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pause_loop.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/25 18:53:18 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 09:44:24 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void	get_pos(int *posx, int *posy, int x, int y)
{
	t_env		*env;

	env = g_env(NULL);
	*posy = (y - (env->arena.space + env->arena.space * 10)) /
			(env->arena.square_size_y + env->arena.space);
	*posx = (x - (env->arena.space + env->arena.space * 10)) /
			(env->arena.square_size_x + env->arena.space);
}

void	info_process(int x, int y, t_data *data, unsigned long cycle_local)
{
	t_env		*env;
	SDL_Rect	rect;
	int			posx;
	int			posy;

	env = g_env(NULL);
	if (env->pause)
	{
		get_pos(&posx, &posy, x, y);
		rect.y = env->arena.space + env->arena.space * 10;
		rect.x = env->arena.space + env->arena.space * 10;
		rect.h = env->arena.square_size_y * 64 + env->arena.space * 64 -
			env->arena.space;
		rect.w = env->arena.square_size_x * 64 + env->arena.space * 64 -
			env->arena.space;
		print_image(NULL, "corewar_background.jpg");
		SDL_FillRect(env->screen, &rect, 0x777777);
		visu_interface(data, cycle_local);
		print_arena(data);
		highlight_process(data);
		if (posx < 64 && posy < 64 && posx >= 0 && posy >= 0)
			process_present(data->pchain, posy * 64 + posx);
		SDL_UpdateWindowSurface(env->pwindow);
	}
}
