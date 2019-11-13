/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin_f.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 15:17:50 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 16:59:27 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_f(char *s1, char *s2, int free)
{
	char *str;

	str = NULL;
	if (!s1 && !(s1 = ft_strnew(0)))
		return (NULL);
	if (!s2 && !(s2 = ft_strnew(0)))
		return (NULL);
	str = ft_strjoin(s1, s2);
	if (free & 1)
		ft_strdel(&s1);
	if (free & 2)
		ft_strdel(&s2);
	return (str);
}
