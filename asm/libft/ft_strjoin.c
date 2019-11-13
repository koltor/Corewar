/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 15:41:08 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 16:57:52 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *fs;

	fs = NULL;
	if (s1 && s2)
	{
		if (!(fs = ft_strnew((ft_strlen(s1) + ft_strlen(s2)))))
			return (NULL);
		return (ft_strcat(ft_strcat(fs, s1), s2));
	}
	return (NULL);
}
