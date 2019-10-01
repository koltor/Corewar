/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_champ_sf.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 10:16:49 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 13:14:57 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** unsigned_int_reverse_bit permet de transformer un unsigned int coder en
** Big endian vers un Little endian
** utile pour passer le magic number et la taille du programme de
** l'un a l'autre
*/

static unsigned int	unsigned_int_reverse_bit(unsigned int n)
{ 
    unsigned int rev;

	rev = n & 0xff000000;
	rev = rev >> 8;
	n = n << 8;
	rev = rev | (n & 0xff000000);
	rev = rev >> 8;
	n = n << 8;
	rev = rev | (n & 0xff000000);
	rev = rev >> 8;
	n = n << 8;
	rev = rev | (n & 0xff000000);
	return (rev);
}

/*
** get_data_of_champ recupere les information de header du champion
** actuellement traite.
** passe les valeurs magic et taille du programme de
** Big Endian vers Little Endian
*/

void	get_data_of_champ(t_header *header, const char src[])
{
    ft_memcpy(header, src, sizeof(*header));
	header->magic = unsigned_int_reverse_bit(header->magic);
	header->prog_size = unsigned_int_reverse_bit(header->prog_size);
}
