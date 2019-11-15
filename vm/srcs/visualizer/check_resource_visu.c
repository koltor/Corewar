/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_resource_visu.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 17:12:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 17:22:36 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

static t_bool	check_image(char *img_name)
{
	char				*path;
	static SDL_Surface	*image;

	path = get_assets_path(img_name, 0);
	image = IMG_Load(path);
	free(path);
	if (image)
	{
		SDL_FreeSurface(image);
		return (TRUE);
	}
	return (FALSE);
}

t_bool			check_visu_ressource(void)
{
	t_env				*env;
	int					i;

	env = g_env(NULL);
	i = -1;
	if (!env->police1 || !env->police2)
		return (FALSE);
	while (++i < 16)
		if (!env->sound[i])
			return (FALSE);
	if (!check_image("corewar_background.jpg") ||
						!check_image("corewar_intro.jpg"))
		return (FALSE);
	return (TRUE);
}
