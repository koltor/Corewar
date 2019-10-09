/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 14:27:02 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 17:40:25 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# define FORMAT ".#0+- hlL"
# define TYPES "spdiouxXcefg"
# define LENGTH "hlL"
# define FLAGS "#0-+ "
# define NULLSTR "(null)"
# define COLORS "dDrRgGyYbBmMcC"
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define UINT_MAX 4294967295
# define LONG_MAX 9223372036854775807U
# define LONG_MIN -9223372036854775808U
# define ULONG_MAX 18446744073709551615U

enum	e_bool
{
		true = 1,
		false = 0
};

typedef enum e_bool	t_bool;

typedef struct	s_flags
{
	t_bool	hashtag;
	t_bool	minus;
	t_bool	plus;
	t_bool	zero;
	t_bool	space;
	t_bool	coma;
}				t_flags;

typedef struct	s_format
{
	struct s_flags	*flags;
	size_t			width;
	t_bool			point;
	size_t			precision;
	char			*length;
	char			type;
}				t_format;

typedef struct	s_expr
{
	char			*expr;
	size_t			length;
	struct s_format	*format;
	struct s_expr	*next;
}				t_expr;

int				ft_printf(const char *format, ...)
				 __attribute__((format(printf,1,2)));
t_expr			*create_new_t_expr(void);
t_format		*create_new_t_format(void);
t_flags			*create_new_t_flags(void);
char			*get_flags(const char *sub_expr);
char			*get_width(const char *sub_expr);
char			*get_precision(const char *sub_expr);
char			*get_length(const char *sub_expr);
t_bool			set_flags(t_format *format, char *flags);
int				set_width(t_format *format, char *width);
int				set_point(t_format *format, const char *sub_expr);
int				set_precision(t_format *format, char *precision);
int				set_length(t_format *format, char *length);
char			*convert_string(t_format *format, size_t *len, va_list args);
char			*convert_decimal(t_format *format, size_t *len, va_list args);
char			*convert_octal(t_format *format, size_t *len, va_list args);
char			*convert_hexa(t_format *format, size_t *len, va_list args);
char			*convert_unsigned(t_format *format, size_t *len, va_list args);
char			*convert_character(t_format *format, size_t *len, va_list args);
char			*convert_pointer(t_format *format, size_t *len, va_list args);
char			*format_character(t_format *format, size_t *len, char arg);
char			*ft_ldtoa(long double nbr, t_format *format);
char			*convert_float(t_format *format, size_t *len, va_list args);
t_bool			parse_expression(const char *expr, t_expr **first);
char			*manage_colors(t_expr *curr);

#endif
