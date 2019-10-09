/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hexdump.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 10:15:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/03 11:47:38 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_in_hexa(unsigned int nb, int precision)
{
	const char base[16] = "0123456789abcdef";

	if (nb / 16 > 0)
		ft_putnbr_in_hexa(nb / 16, precision - 1);
	else if (precision > 1)
		ft_putnbr_in_hexa(nb / 16, precision - 1);
	ft_putchar(base[nb % 16]);
}

void		ft_hexdump(void *mem, unsigned int len)
{
	unsigned int i;

	i = 0;
	while (i < len)
	{
		if (i % HEXDUMP_COLS == 0)
		{
			ft_putstr("0x");
			ft_putnbr_in_hexa(i, 4);
			ft_putstr(" : ");
		}
		ft_putnbr_in_hexa(0xFF & ((char*)mem)[i], 2);
		ft_putstr(" ");
		if (i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
			ft_putchar('\n');
		i++;
	}
}
