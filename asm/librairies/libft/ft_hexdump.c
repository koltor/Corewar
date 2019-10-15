/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hexdump.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 10:15:46 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 16:59:18 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	write_adress(char *buff, const char base[16], short *pos, int i)
{
	buff[*pos] = '0';
	buff[*pos + 1] = 'x';
	buff[*pos + 2] = base[(i / 4096) % 16];
	buff[*pos + 3] = base[(i / 256) % 16];
	buff[*pos + 4] = base[(i / 16) % 16];
	buff[*pos + 5] = base[i % 16];
	buff[*pos + 6] = ' ';
	buff[*pos + 7] = ':';
	buff[*pos + 8] = ' ';
	*pos += 8;
}

void		ft_hexdump(void *mem, unsigned int len)
{
	const char		base[16] = "0123456789abcdef";
	unsigned int	i;
	short			pos;
	char			buff[12928];

	i = 0;
	pos = 0;
	while (i < len)
	{
		if (i % HEXDUMP_COLS == 0)
			write_adress(&buff[0], base, &pos, (int)i);
		buff[pos] = base[((0xFF & ((char*)mem)[i]) / 16) % 16];
		buff[pos + 1] = base[(0xFF & ((char*)mem)[i]) % 16];
		buff[pos + 2] = ' ';
		pos += 3;
		if (i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
		{
			buff[pos++] = '\n';
		}
		i++;
	}
	write(1, &buff, 12928);
}
