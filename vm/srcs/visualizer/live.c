/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   live.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/31 15:29:12 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 13:34:45 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void		set_live_visu(char id)
{
	t_env *env;

	env = g_env(NULL);
	env->champ_live[(int)id] += 1;
	env->champ_live[0] += 1;
}

void		set_live_visu_bzero(void)
{
	t_env *env;

	env = g_env(NULL);
	ft_bzero(env->champ_live, sizeof(env->champ_live));
}

static void	print_live_name(t_data *data)
{
	t_env			*env;
	SDL_Rect		rect;

	env = g_env(NULL);
	rect.x = env->win_size.x - (env->win_size.x / 18) * 3;
	rect.y = env->win_size.y - 100;
	rect.h = env->win_size.y / 25;
	rect.w = (env->win_size.x / 18) * 2;
	print_text("Dernier live", &rect, (SDL_Color){200, 200, 200, 0},
													env->police1);
	rect.y = env->win_size.y - 50;
	rect.h = env->win_size.y / 25;
	if (data->last_player_alive != -1)
		print_text(data->champs_data[data->last_player_alive].prog_name,
					&rect, (SDL_Color){175, 175, 175, 0}, env->police1);
	else
		print_text("Nobody", &rect, (SDL_Color){175, 175, 175, 0},
													env->police1);
}

static void	fill_live_bar(SDL_Rect *rect, t_data *data)
{
	const int	color[4] = {
		0xC87F1C, 0xA22717, 0x259E17, 0x7536ab
	};
	int			i;
	int			width;
	t_env		*env;

	i = 0;
	env = g_env(NULL);
	width = rect->w;
	if (env->champ_live[0] == 0)
		return ;
	while (i < data->nb_champ)
	{
		rect->w *= ((float)env->champ_live[i + 1] / (float)env->champ_live[0]);
		SDL_FillRect(env->screen, rect, color[i]);
		rect->x += rect->w;
		rect->w = width;
		i++;
	}
}

void		live_bar(t_data *data)
{
	t_env			*env;
	SDL_Rect		rect;

	env = g_env(NULL);
	rect.x = env->arena.space * 10;
	rect.w = env->arena.square_size_x * 64 + env->arena.space * 64 - 40;
	rect.y = env->win_size.y - 40;
	rect.h = 10;
	draw_empty_rect(&rect, 15784682, 2);
	fill_live_bar(&rect, data);
	rect.x = env->arena.square_size_x * 64 + env->arena.space * 64;
	rect.w = 30;
	print_value(env->champ_live[0], &rect, (SDL_Color){175, 175, 175, 0},
														env->police2);
	print_live_name(data);
}
