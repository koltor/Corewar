/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_memory2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 14:40:10 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 14:10:30 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	fill_hex_res(char res[], int rem, unsigned char *val)
{
	const char hex[16] = "0123456789abcdef";

	res[rem - 1] = hex[*val % 16];
	*val /= 16;
	if (rem > 1)
		fill_hex_res(res, rem - 1, val);
}

void	print_octet_hex(unsigned char *p)
{
	char res[2];

	res[0] = '0';
	res[1] = '0';
	fill_hex_res(res, 2, p);
	write(1, &res, 2);
}

void	print_last_octet(unsigned char *p)
{
	char res[2];

	res[0] = '0';
	res[1] = '0';
	write(1, &res, 2);
	fill_hex_res(res, 2, p);
	write(1, &res, 2);
}

void	print_memory_hexa(const void *addr, size_t size)
{
	unsigned char	*p;
	int				i;
	int				odd;

	i = 0;
	odd = 0;
	if ((size % 2) != 0)
		odd = 1;
	p = (unsigned char *)addr;
	while (i < (int)size)
	{
		if (i % 16 == 0 && i != 0)
			write(1, "\n", 1);
		else
			print_octet_hex(p);
		write(1, " ", 1);
		p++;
		i++;
	}
}

void	print_memory_hexa_memsize(const void *addr, size_t size, int start,
																int mem_size)
{
	unsigned char	*p;
	int				i;
	int				odd;

	i = 0;
	odd = 0;
	if ((size % 2) != 0)
		odd = 1;
	p = (unsigned char *)addr;
	while (i < (int)size)
	{
		if (start % mem_size == 0 && start != 0)
		{
			p = p - mem_size;
			start = 0;
		}
		if (i % 16 == 0 && i != 0)
			write(1, "\n", 1);
		else
			print_octet_hex(p);
		write(1, " ", 1);
		start++;
		p++;
		i++;
	}
}
