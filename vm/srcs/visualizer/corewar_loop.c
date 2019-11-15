/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar_loop.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 18:42:40 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 15:35:21 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

t_bool		loop_corewar(t_data *data, unsigned long cycle_local)
{
	t_env		*k;
	SDL_Rect	rect;

	k = g_env(NULL);
	rect.y = k->arena.space + k->arena.space * 10;
	rect.x = k->arena.space + k->arena.space * 10;
	rect.h = k->arena.square_size_y * 64 + k->arena.space * 64 - k->arena.space;
	rect.w = k->arena.square_size_x * 64 + k->arena.space * 64 - k->arena.space;
	if (!(data->cycle % k->time))
	{
		print_image(NULL, "corewar_intro.jpg");
		SDL_FillRect(k->screen, &rect, 0x777777);
		visu_interface(data, cycle_local);
		print_arena(data);
		highlight_process(data);
		SDL_UpdateWindowSurface(k->pwindow);
		if (sdl_loop(SDL_GetTicks() + 1, data, cycle_local) == 2)
		{
			k->forced_to_quit = TRUE;
			return (FALSE);
		}
	}
	return (TRUE);
}
