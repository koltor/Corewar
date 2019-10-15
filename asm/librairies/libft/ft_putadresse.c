/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putadresse.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/11 09:51:40 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/03 09:53:02 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_putadresse2(unsigned long long adr)
{
	const char base[] = "0123456789abcdef\0";

	if (adr / 16 > 0)
		ft_putadresse2(adr / 16);
	ft_putchar(base[adr % 16]);
}

void			ft_putadresse(const void *adresse)
{
	unsigned long long adr;

	ft_putstr("0x");
	adr = (unsigned long long)adresse;
	ft_putadresse2(adr);
}
