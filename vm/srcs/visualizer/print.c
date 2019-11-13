/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/25 16:21:55 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 18:10:05 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

void	print_image(SDL_Rect *pos, char *img_name)
{
	static SDL_Surface	*image;
	char				*path;
	t_env				*env;

	env = g_env(NULL);
	path = get_assets_path(img_name, 0);
	image = IMG_Load(path);
	free(path);
	SDL_BlitScaled(image, 0, env->screen, pos);
	SDL_FreeSurface(image);
}

void	print_text(char *str, SDL_Rect *rect, SDL_Color color, TTF_Font *font)
{
	t_env		*env;
	SDL_Surface	*text;

	env = g_env(NULL);
	text = TTF_RenderText_Blended(font, str, color);
	SDL_BlitScaled(text, 0, env->screen, rect);
	SDL_FreeSurface(text);
}

void	print_value(int value, SDL_Rect *rect, SDL_Color color, TTF_Font *font)
{
	char	*string;

	string = ft_itoa(value);
	print_text(string, rect, color, font);
	free(string);
}

void	print_value_hexa(int v, SDL_Rect *rect, SDL_Color clr, TTF_Font *font)
{
	char	*string;

	string = ft_itoa_base(v, 16);
	print_text(string, rect, clr, font);
	free(string);
}

void	draw_empty_rect(SDL_Rect *origin, int color, int thickness)
{
	t_env		*env;
	SDL_Rect	ligne;

	env = g_env(NULL);
	ligne.x = origin->x - 1;
	ligne.y = origin->y - 1;
	ligne.w = origin->w + 1;
	ligne.h = thickness;
	SDL_FillRect(env->screen, &ligne, color);
	ligne.x = origin->x - 1;
	ligne.y = origin->y - 1;
	ligne.w = thickness;
	ligne.h = origin->h + 1;
	SDL_FillRect(env->screen, &ligne, color);
	ligne.x = origin->x + origin->w;
	ligne.y = origin->y - 1;
	ligne.w = thickness;
	ligne.h = origin->h + 1;
	SDL_FillRect(env->screen, &ligne, color);
	ligne.x = origin->x - 1;
	ligne.y = origin->y + origin->h;
	ligne.w = origin->w + 1 + thickness;
	ligne.h = thickness;
	SDL_FillRect(env->screen, &ligne, color);
}
