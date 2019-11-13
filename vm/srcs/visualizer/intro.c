/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   intro.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 17:45:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 14:48:14 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void		intro(void)
{
	t_env			*env;
	static SDL_Rect	pos = {WIN_SIZE_X / 2 - 200, 50, 400, 100};

	env = NULL;
	env = g_env(NULL);
	print_image(NULL, "corewar_intro.jpg");
	print_text("Corewar", &pos, (SDL_Color){0, 0, 0, 0}, env->police1);
	SDL_UpdateWindowSurface(env->pwindow);
	sdl_loop(5000, NULL, 0);
}
