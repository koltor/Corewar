/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sdl_loop.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 17:50:18 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 16:16:11 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

static char	sdl_keydown_event(SDL_KeyboardEvent key, t_data *data)
{
	t_env	*env;

	env = g_env(NULL);
	if (key.keysym.sym == SDLK_KP_ENTER)
		return (1);
	else if (key.keysym.sym == SDLK_SPACE)
		env->pause = (env->pause == TRUE) ? FALSE : TRUE;
	else if (key.keysym.sym == 1073741911 && env->time < 128)
		env->time *= 2;
	else if (key.keysym.sym == 1073741910 && env->time > 1)
		env->time /= 2;
	else if (key.keysym.sym == SDLK_ESCAPE)
		return (2);
	(void)data;
	return (0);
}

static char	sdl_windows_event(SDL_WindowEvent window, t_data *data)
{
	t_env	*env;

	env = g_env(NULL);
	if (window.event == SDL_WINDOWEVENT_CLOSE)
		return (2);
	else if (window.event == SDL_WINDOWEVENT_RESIZED)
	{
		SDL_GetWindowSize(env->pwindow, &env->win_size.x, &env->win_size.y);
		env->screen = SDL_GetWindowSurface(env->pwindow);
		init_arena();
	}
	(void)data;
	return (0);
}

static void	sdl_mouse_event(t_data *data, unsigned long cycle)
{
	int	x;
	int	y;

	if (!data)
		return ;
	SDL_GetMouseState(&x, &y);
	info_process(x, y, data, cycle);
}

char		sdl_loop(unsigned long time, t_data *data, unsigned long cycle)
{
	SDL_Event	ev;
	t_env		*env;
	char		ret;

	env = g_env(NULL);
	ret = 0;
	while (SDL_GetTicks() < time || time == 0 || env->pause == TRUE)
	{
		SDL_PollEvent(&ev);
		if (ev.type == SDL_KEYDOWN)
		{
			if ((ret = sdl_keydown_event(ev.key, data)))
				break ;
		}
		else if (ev.type == SDL_WINDOWEVENT)
		{
			if ((ret = sdl_windows_event(ev.window, data)))
				break ;
		}
		else if (ev.type == SDL_MOUSEMOTION && data != NULL)
			sdl_mouse_event(data, cycle);
		else if (time == 5000 && env->pause == TRUE)
			break ;
	}
	return (ret);
}
