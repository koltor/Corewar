/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim_f.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/28 09:17:37 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 14:31:24 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_f(char *str)
{
	char *new_str;

	new_str = NULL;
	if (!(new_str = ft_strtrim(str)))
		return (NULL);
	ft_strdel(&str);
	return (new_str);
}
