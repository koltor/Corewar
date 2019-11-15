/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_visu.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/21 13:49:44 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 17:14:23 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void			init_arena(void)
{
	t_env	*env;
	int		i;

	env = g_env(NULL);
	env->arena.space = 3;
	env->arena.square_size_x = (env->win_size.x - (64 * env->arena.space) -
		(env->win_size.x / 5) - (env->arena.space * 20)) / 64;
	env->arena.square_size_y = (env->win_size.y - (64 * env->arena.space) -
		(env->arena.space * 20)) / 64;
	i = 0;
	while (i < MEM_SIZE)
	{
		env->arena.rect[i].h = env->arena.square_size_y;
		env->arena.rect[i].w = env->arena.square_size_x;
		env->arena.rect[i].y = (i / 64) * env->arena.square_size_y +
			env->arena.space * (i / 64) + env->arena.space +
				env->arena.space * 10;
		env->arena.rect[i].x = (i % 64) * env->arena.square_size_x +
		env->arena.space * (i % 64) + env->arena.space + env->arena.space * 10;
		i++;
	}
}

static char		*get_exec_path(char *name)
{
	int n;
	int tmp;

	n = -1;
	tmp = 0;
	while (name[++n])
	{
		if (name[n] == '/')
			tmp = n + 1;
	}
	name[tmp] = 0;
	return (ft_strdup(name));
}

static void		get_policy(void)
{
	char	*path;
	t_env	*env;

	env = g_env(NULL);
	path = get_assets_path("unispace.ttf", 1);
	env->police2 = TTF_OpenFont(path, 65);
	free(path);
	path = get_assets_path("Positive System.otf", 1);
	env->police1 = TTF_OpenFont(path, 65);
	free(path);
}

static t_bool	init_env(char *path_name)
{
	t_env	*env;

	env = g_env(NULL);
	env->pwindow = SDL_CreateWindow("Visualizer Corewar",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_SIZE_X,
		WIN_SIZE_Y, SDL_WINDOW_SHOWN);
	env->screen = SDL_GetWindowSurface(env->pwindow);
	env->visu_path = get_exec_path(path_name);
	env->win_size.x = WIN_SIZE_X;
	env->win_size.y = WIN_SIZE_Y;
	env->forced_to_quit = FALSE;
	get_policy();
	env->time = 1;
	env->pause = FALSE;
	ft_bzero(env->champ_live, sizeof(env->champ_live));
	init_arena();
	sound_bank_init();
	return (TRUE);
}

t_bool			init_sdl(char *path)
{
	static t_env env;

	if (SDL_Init(SDL_INIT_EVERYTHING) || TTF_Init())
		return (FALSE);
	if (Mix_OpenAudio(11025, AUDIO_S8, MIX_DEFAULT_CHANNELS, 1024))
		return (FALSE);
	g_env(&env);
	init_env(path);
	if (!check_visu_ressource())
		return (FALSE);
	play_music();
	intro();
	return (TRUE);
}
