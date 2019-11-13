/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_param_type.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/12 16:10:15 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 14:00:03 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

char	get_param_type(char ocp, char param)
{
	const char v[4] = {
		(ocp & 0xc0) >> 6, (ocp & 0x30) >> 4, (ocp & 0xc) >> 2, ocp & 0x3
	};

	return (v[param - 1]);
}
