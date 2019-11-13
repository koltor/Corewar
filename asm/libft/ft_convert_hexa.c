/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_hexa.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 19:38:34 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 14:46:39 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*set_str(t_format *format, size_t len, char c)
{
	char	*str;
	size_t	l;

	str = NULL;
	l = 0;
	if (c == '0')
	{
		if (format->point)
		{
			l = (format->precision > len) ?
				format->precision - len : 0;
		}
		else if (format->flags && format->flags->zero)
			l = (format->width > len) ? format->width - len : 0;
	}
	else if (c == ' ')
		l = format->width > len ? format->width - len : 0;
	if (!(str = ft_strnew(l)))
		return (NULL);
	ft_memset((void *)str, c, l);
	return (str);
}

static char	*set_hashtag(char *str, t_bool is_null, t_bool has_prec)
{
	if (is_null)
		return (str);
	if (*str == '0' && !has_prec)
	{
		if (*(str + 1) == '0')
			str[1] = 'x';
		else
		{
			str[0] = 'x';
			str = ft_strjoin_f("0", str, 2);
		}
	}
	else
		str = ft_strjoin_f("0x", str, 2);
	return (str);
}

char		*format_hexa(t_format *format, size_t *length,
									unsigned long nbr)
{
	char	*str;
	size_t	len;

	str = NULL;
	ft_ulltoa_base(&str, nbr, 16);
	len = ft_strlen(str);
	str = ft_strjoin_f(set_str(format, len, '0'), str, 3);
	if (nbr == 0 && format->point && format->precision == 0)
	{
		free(str);
		str = ft_strnew(0);
	}
	if (format->flags && format->flags->hashtag)
		str = set_hashtag(str, nbr == 0, format->point);
	if (format->flags && format->flags->minus)
		str = ft_strjoin_f(str, set_str(format, ft_strlen(str), ' '), 3);
	else
		str = ft_strjoin_f(set_str(format, ft_strlen(str), ' '), str, 3);
	*length = ft_strlen(str);
	return (str);
}

char		*convert_hexa(t_format *format, size_t *len, va_list args)
{
	if (format->length)
	{
		if (ft_strcmp("hh", format->length) == 0)
		{
			return (format_hexa(format, len,
			(unsigned long)(unsigned char)va_arg(args, unsigned int)));
		}
		if (ft_strcmp("h", format->length) == 0)
		{
			return (format_hexa(format, len,
			(unsigned long)(unsigned short)va_arg(args, unsigned int)));
		}
		if (ft_strcmp("l", format->length) == 0)
		{
			return (format_hexa(format, len,
			va_arg(args, unsigned long)));
		}
		if (ft_strcmp("ll", format->length) == 0)
		{
			return (format_hexa(format, len,
			(unsigned long)va_arg(args, unsigned long long)));
		}
	}
	return (format_hexa(format, len,
			(unsigned long)va_arg(args, unsigned int)));
}
