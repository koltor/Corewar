/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/12 08:22:55 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 16:04:35 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_corewar.h"

/*
** get_background_img_path permet de recuperer le chemin vers un asset en
** fonction de son type et de son nom.
** type à 0 = IMAGE
** type à 1 = POLICE D'ECRITURE
*/

char		*get_assets_path(char *name, int type)
{
	t_env		*env;
	char		*path;
	char		*tmp;
	const char	*src_tab[3] = {RESOURCES_VISU_IMG, RESOURCES_VISU_FONT,
													RESOURCES_VISU_SOUND};

	env = g_env(NULL);
	tmp = ft_strjoin(env->visu_path, src_tab[type]);
	path = ft_strjoin(tmp, name);
	free(tmp);
	return (path);
}
