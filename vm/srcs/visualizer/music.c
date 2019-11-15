/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   music.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 14:40:06 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 17:10:50 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

static char	*music_bank_path(int num)
{
	const char	*tab[6] = {
		"barbie_girl.mid",
		"beat_it.mid",
		"erasure_always.mid",
		"eye_of_the_tiger.mid",
		"flight_of_the_bumble_bee.mid",
		"ghostbusters.mid",
	};

	return (get_assets_path((char*)tab[num], 2));
}

void		play_music(void)
{
	char		*path;
	Mix_Music	*mus;
	int			value;

	value = my_rand(6);
	path = music_bank_path(value);
	mus = Mix_LoadMUS(path);
	Mix_PlayMusic(mus, -1);
	free(path);
}

static char	*sound_bank_path(char opc)
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

void		sound_bank_init(void)
{
	int			i;
	char		*path;
	t_env		*env;

	i = -1;
	env = g_env(NULL);
	while (++i < 16)
	{
		path = sound_bank_path(i + 1);
		env->sound[i] = Mix_LoadWAV(path);
		free(path);
		if (!env->sound[i])
			continue ;
		Mix_VolumeChunk(env->sound[i], 7);
	}
}

void		play_sound(char opc)
{
	t_env		*env;

	env = g_env(NULL);
	Mix_PlayChannel(-1, env->sound[opc - 1], 0);
}
