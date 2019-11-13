/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   info_process_sf.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 10:01:55 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 13:57:25 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

static void		show_metadata_process_title2(t_process *process)
{
	SDL_Rect		rect;
	t_env			*env;

	env = g_env(NULL);
	rect.x = env->win_size.x - (env->win_size.x / 18) * 2 - 150;
	rect.w = env->win_size.x / 28;
	rect.y = 600;
	rect.h = 320;
	rect.w *= 4;
	draw_empty_rect(&rect, 0xeeeeee, 2);
	rect.y -= 50;
	rect.h = 40;
	print_text("Les Registres", &rect, (SDL_Color){175, 50, 50, 0},
															env->police1);
}

void			show_metadata_process_title(t_process *process)
{
	SDL_Rect		rect;
	const SDL_Color	color = {175, 175, 175, 0};
	t_env			*env;

	env = g_env(NULL);
	rect.x = env->win_size.x - (env->win_size.x / 18) * 2 - 150;
	rect.w = env->win_size.x / 28;
	rect.y = 200;
	rect.h = 20;
	print_text("process", &rect, color, env->police2);
	rect.y += 40;
	print_text("en vie", &rect, color, env->police2);
	rect.y += 40;
	print_text("carry", &rect, color, env->police2);
	rect.y += 40;
	print_text("position", &rect, color, env->police2);
	rect.y += 40;
	print_text("instruction", &rect, color, env->police2);
	rect.y += 40;
	print_text("parametre", &rect, color, env->police2);
	rect.y += 40;
	print_text("cycle", &rect, color, env->police2);
	show_metadata_process_title2(process);
}

static void		show_ocp_params(int mx, char ocp, SDL_Rect *rect, TTF_Font *ply)
{
	int		i;
	char	r;
	char	k[7];

	i = 0;
	while (i < mx)
	{
		if ((r = get_param_type(ocp, i + 1)) == 1)
			(i + 1 != mx) ? ft_strcpy(k, "REG - \0") : ft_strcpy(k, "REG   \0");
		else if (r == 2)
			(i + 1 != mx) ? ft_strcpy(k, "DIR - \0") : ft_strcpy(k, "DIR   \0");
		else
			(i + 1 != mx) ? ft_strcpy(k, "IND - \0") : ft_strcpy(k, "IND   \0");
		print_text(k, rect, (SDL_Color){200, 140, 79}, ply);
		rect->x += rect->w;
		i++;
	}
}

void			show_metadata_process2(t_process *process)
{
	SDL_Rect	rect;
	t_env		*env;

	env = g_env(NULL);
	rect.x = env->win_size.x - (env->win_size.x / 18) * 2 - 150 +
											env->win_size.x / 28 * 2;
	rect.w = env->win_size.x / 28;
	rect.y = 400;
	rect.h = 20;
	if (g_op_tab[process->opc_curr - 1].use_ocp)
	{
		rect.w = env->win_size.x / 54;
		show_ocp_params(g_op_tab[process->opc_curr - 1].param_count,
								process->ocp_curr, &rect, env->police2);
		rect.w = env->win_size.x / 28;
		rect.x = env->win_size.x - (env->win_size.x / 18) * 2 - 150 +
												env->win_size.x / 28 * 2;
	}
	else
		print_text("aucun ocp", &rect, (SDL_Color){200, 140, 79}, env->police2);
	rect.y += 40;
	(!process->opc_curr) ?
		print_text("---", &rect, (SDL_Color){200, 140, 79}, env->police2) :
		print_value(process->cycle, &rect, (SDL_Color){200, 140, 79},
															env->police2);
}

void			show_metadata_process(t_process *process)
{
	SDL_Rect	rect;
	t_env		*env;
	char		txt[11];

	env = g_env(NULL);
	rect.x = env->win_size.x - (env->win_size.x / 18) * 2 - 150 +
											env->win_size.x / 28 * 2;
	rect.w = env->win_size.x / 28;
	rect.y = 200;
	rect.h = 20;
	print_value(process->id, &rect, (SDL_Color){200, 140, 79}, env->police2);
	rect.y += 40;
	(process->is_alive == true) ? ft_strcpy(txt, "En vie\0") :
										ft_strcpy(txt, "Mort !!!\0");
	print_text(txt, &rect, (SDL_Color){200, 140, 79}, env->police2);
	rect.y += 40;
	(process->carry == true) ? ft_strcpy(txt, "On\0") : ft_strcpy(txt, "Off\0");
	print_text(txt, &rect, (SDL_Color){200, 140, 79}, env->police2);
	rect.y += 40;
	print_value(process->pc, &rect, (SDL_Color){200, 140, 79}, env->police2);
	rect.y += 40;
	(process->opc_curr) ?
		ft_strcpy(txt, g_op_tab[process->opc_curr - 1].name) :
		ft_strcpy(txt, "Vide\0");
	print_text(txt, &rect, (SDL_Color){200, 140, 79}, env->police2);
}
