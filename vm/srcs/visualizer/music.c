/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   music.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 14:40:06 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 17:15:11 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void    play_music(void)
{
	char        *path;
	Mix_Chunk   *mus;

	path = get_assets_path("erasure.wav", 2);
	mus = Mix_LoadWAV(path);
	free(path);
	Mix_PlayChannel(1, mus, 0);
}

char	*sound_bank_path(char opc)
{
	const char *tab[16] = {
		"live.wav",
		"windows.wa",
		"",
		"windows.wa",
		"windows.wa",
		"windows.wa",
		"windows.wa",
		"windows.wa",
		"resors.wav",
		"windows.wa",
		"windows.wa",
		"zjmp.wav",
		"windows.wa",
		"windows.wa",
		"windows.wa",
		"windows.wa"
	};

	return (get_assets_path((char*)tab[opc - 1], 2));
}

void	sound_bank_init(void)
{
	int			i;
	char		*path;
	t_env		*env;

	i = 0;
	env = g_env(NULL);
	while (i < 16)
	{
		path = sound_bank_path(i + 1);
		env->sound[i] = Mix_LoadWAV(path);
		free(path);
		i++;
	}
}


void    play_sound(char opc)
{
	// t_env		*env;
	// static 		int i = 0;
	
	// env = g_env(NULL);
	// dprintf(1, "%s-->%p\n", g_op_tab[opc - 1].name, env->sound[opc - 1]);
    // Mix_PlayChannel(-1, env->sound[opc - 1], 0);
}