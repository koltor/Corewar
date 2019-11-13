/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   footprint.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/28 16:33:27 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 13:34:45 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

static int	get_pc(int nb_champs, int n_champ)
{
	float	section;
	int		i;

	if (nb_champs != 0)
		section = MEM_SIZE / nb_champs;
	else
		section = MEM_SIZE;
	if (section - (int)section > 0.5)
		section = section + 1.0;
	i = n_champ * (int)section;
	return (i);
}

void		print_footprint(int idx, int len, int n)
{
	t_env	*env;
	int		i;

	i = 0;
	env = g_env(NULL);
	while (i < len)
	{
		env->foot_print[(idx + i) % MEM_SIZE] = n;
		i++;
	}
}

void		init_foot_print(t_data *data)
{
	t_env	*env;
	int		i;
	int		pc;

	i = 0;
	env = g_env(NULL);
	ft_bzero(env->foot_print, MEM_SIZE);
	while (i < data->nb_champ)
	{
		pc = get_pc(data->nb_champ, i);
		print_footprint(pc, data->champs_data[i].prog_size, i + 1);
		i++;
	}
}
