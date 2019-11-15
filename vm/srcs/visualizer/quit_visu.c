/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quit_visu.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 17:43:47 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 15:00:02 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void		quit_sdl(void)
{
	t_env	*env;
	int		i;

	env = NULL;
	env = g_env(NULL);
	i = -1;
	if (env->forced_to_quit == TRUE)
		ft_printf("Partie Annuler !\n");
	free(env->visu_path);
	TTF_CloseFont(env->police1);
	TTF_CloseFont(env->police2);
	while (++i < 16)
		Mix_FreeChunk(env->sound[i]);
	SDL_DestroyWindow(env->pwindow);
	SDL_Quit();
}
