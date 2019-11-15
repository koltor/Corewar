/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   winner.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 15:00:21 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 16:20:08 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

static char	*insert_space(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	dest = ft_strnew(ft_strlen(str) * 2);
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[i * 2] = str[i];
		dest[i * 2 + 1] = ' ';
		i++;
	}
	dest[i * 2] = '\0';
	return (dest);
}

static void	print_winner_name(t_data *data)
{
	SDL_Rect		rect;
	t_env			*env;
	const SDL_Color	color = {255, 255, 255, 0};
	char			*player_name;

	env = g_env(NULL);
	player_name = NULL;
	rect.x = env->arena.square_size_x * 20;
	rect.y = env->win_size.y - 70;
	rect.h = 70;
	rect.w = 160;
	if (data->last_player_alive == -1)
	{
		print_text("D r a w", &rect, color, env->police2);
		return ;
	}
	player_name = data->champs_data[data->last_player_alive].prog_name;
	player_name = insert_space(player_name);
	rect.w = ft_strlen(player_name) * 20;
	print_text(player_name, &rect, color, env->police2);
	free(player_name);
	rect.x += rect.w + 50;
	rect.w = 160;
	print_text("W o n !", &rect, color, env->police2);
}

void		show_the_winner(t_data *data, unsigned long cycle_local)
{
	t_env		*env;
	SDL_Rect	rect;

	env = g_env(NULL);
	if (env->forced_to_quit)
		return ;
	rect.y = env->arena.space + env->arena.space * 10;
	rect.x = env->arena.space + env->arena.space * 10;
	rect.h = env->arena.square_size_y * 64 +
		env->arena.space * 64 - env->arena.space;
	rect.w = env->arena.square_size_x * 64 +
		env->arena.space * 64 - env->arena.space;
	print_image(NULL, "corewar_intro.jpg");
	SDL_FillRect(env->screen, &rect, 0x777777);
	print_arena(data);
	print_variable(data, cycle_local);
	print_winner_name(data);
	SDL_UpdateWindowSurface(env->pwindow);
	env->pause = TRUE;
	sdl_loop(SDL_GetTicks() + 1, NULL, cycle_local);
}
