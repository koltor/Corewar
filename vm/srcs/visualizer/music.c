/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   music.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 14:40:06 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 17:10:29 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void	play_music(void)
{
	char		*path;
	Mix_Music	*mus;

	path = get_assets_path("eye_of_the_tiger.mid", 2);
	mus = Mix_LoadMUS(path);
	free(path);
	Mix_PlayMusic(mus, -1);
}

char	*sound_bank_path(char opc)
{
	const char	*tab[16] = {
		"live.wav",
		"other.wav",
		"other.wav",
		"other.wav",
		"other.wav",
		"other.wav",
		"other.wav",
		"other.wav",
		"jmp.wav",
		"other.wav",
		"other.wav",
		"fork.wav",
		"other.wav",
		"other.wav",
		"fork.wav",
		"other.wav"
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
		Mix_VolumeChunk(env->sound[i], 7);
		free(path);
		i++;
	}
}

void	play_sound(char opc)
{
	t_env		*env;

	env = g_env(NULL);
	Mix_PlayChannel(-1, env->sound[opc - 1], 0);
}
