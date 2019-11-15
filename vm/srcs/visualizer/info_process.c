/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   info_process.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 09:37:23 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 16:27:00 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

static void		show_registre_process(t_process *process)
{
	SDL_Rect	rect;
	t_env		*env;
	int			i;

	env = g_env(NULL);
	i = 0;
	rect.w = env->win_size.x / 14;
	rect.h = 40;
	while (i < 16)
	{
		rect.y = 600 + ((i % 8) * 40);
		rect.x = (env->win_size.x - (env->win_size.x / 18) * 2 - 150) +
										((i / 8) * env->win_size.x / 14);
		rect.w = 1;
		draw_empty_rect(&rect, 0xeeeeee, 2);
		rect.w = env->win_size.x / 54;
		rect.x += 15;
		print_text("0x", &rect, (SDL_Color){75, 150, 180, 0}, env->police2);
		rect.x += env->win_size.x / 54;
		rect.w *= 2;
		print_value_hexa(process->reg[i], &rect,
					(SDL_Color){75, 150, 180, 0}, env->police2);
		rect.x -= env->win_size.x / 54 - 15;
		i++;
	}
}

void			process_present(t_list *begin, unsigned int pos_process)
{
	show_metadata_process_title();
	while (begin)
	{
		if (((t_process*)(begin->content))->pc == pos_process)
		{
			show_registre_process((t_process*)(begin->content));
			show_metadata_process((t_process*)(begin->content));
			show_metadata_process2((t_process*)(begin->content));
			break ;
		}
		begin = begin->next;
	}
}
