/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_arena.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 19:46:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 16:23:00 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

static char	*get_text_memory(char *arena, int pos, char *text)
{
	const char base[16] = "0123456789ABCDEF";

	text[0] = base[((0xFF & arena[pos]) / 16)];
	text[1] = base[((0xFF & arena[pos]) % 16)];
	return (text);
}

static void	print_text_arena(t_data *data, int i, SDL_Rect rect)
{
	t_env			*env;
	static char		*c = NULL;

	env = g_env(NULL);
	if (c == NULL)
		c = ft_strnew(3);
	c = get_text_memory(data->arena, i, c);
	rect.x += 2;
	rect.y += 2;
	rect.w -= 4;
	rect.h -= 4;
	print_text(c, &rect, (SDL_Color){230, 230, 230, 0}, env->police2);
}

void		print_arena(t_data *data)
{
	t_env		*env;
	int			i;
	const int	clr[5] = {
		0x666666, 0xC87F1C, 0xA22717, 0x259E17, 0x7536ab
	};

	env = g_env(NULL);
	i = 0;
	while (i < MEM_SIZE)
	{
		SDL_FillRect(env->screen, &env->arena.rect[i],
								clr[(int)env->foot_print[i]]);
		print_text_arena(data, i, env->arena.rect[i]);
		i++;
	}
}
