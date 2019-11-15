/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_character.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 19:39:33 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 11:53:00 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*set_str(t_format *format, size_t b)
{
	char	*str;

	str = NULL;
	if (!(str = ft_strnew(format->width > b ? format->width - b : 0)))
		return (NULL);
	ft_memset((void *)str, (format->flags && format->flags->zero) ? '0' : ' ',
				format->width > b ? format->width - b : 0);
	return (str);
}

char		*format_character(t_format *format, size_t *len, char arg)
{
	char	*str;

	str = NULL;
	if (format->flags && format->flags->minus)
	{
		str = ft_strjoin_f(" ", set_str(format, 1), 2);
		*len = ft_strlen(str);
		str[0] = arg;
	}
	else
	{
		str = ft_strjoin_f(set_str(format, 1), " ", 1);
		*len = ft_strlen(str);
		str[*len - 1] = arg;
	}
	return (str);
}

char		*convert_character(t_format *format, size_t *len, va_list args)
{
	return (format_character(format, len, (char)va_arg(args, int)));
}
