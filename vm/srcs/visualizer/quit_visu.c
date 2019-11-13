/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quit_visu.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 17:43:47 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/11 15:46:33 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void		quit_sdl(void)
{
	t_env *env;

	env = NULL;
	g_env(env);
	SDL_DestroyWindow(env->pwindow);
	SDL_Quit();
}
