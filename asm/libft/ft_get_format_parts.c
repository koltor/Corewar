/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_format_parts.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 16:00:57 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 11:31:51 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*get_flags(const char *sub_expr)
{
	char	*flags;
	int		i;

	i = 0;
	flags = NULL;
	while (ft_strctn(FLAGS, *(sub_expr + i)))
		i++;
	if (i > 0)
		flags = ft_strsub(sub_expr, 0, i);
	return (flags);
}

char	*get_width(const char *sub_expr)
{
	char	*width;
	int		i;

	i = 0;
	width = NULL;
	while (ft_isdigit(*(sub_expr + i)))
		i++;
	if (i > 0)
		width = ft_strsub(sub_expr, 0, i);
	return (width);
}

char	*get_precision(const char *sub_expr)
{
	char	*precision;
	int		i;

	i = 0;
	precision = NULL;
	while (ft_isdigit(*(sub_expr + i)))
		i++;
	if (i > 0)
		precision = ft_strsub(sub_expr, 0, i);
	return (precision);
}

char	*get_length(const char *sub_expr)
{
	char	*length;
	int		i;

	i = 0;
	length = NULL;
	while (ft_strctn(LENGTH, *(sub_expr + i)))
		i++;
	if (i > 0)
		length = ft_strsub(sub_expr, 0, i);
	return (length);
}
