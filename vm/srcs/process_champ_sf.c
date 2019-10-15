/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   e_process_champ_sf.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 10:16:49 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:42:32 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** check_id_is_available permet de verifier que l'id est diponible pour une
** affectation
*/

static unsigned int	check_id_is_available(unsigned int id,
										unsigned int n[MAX_PLAYERS], int max_p)
{
	int i;

	i = 0;
	while (i < max_p)
	{
		if (n[i] == id)
			return (0);
		i++;
	}
	return (1);
}

/*
** set_n_number permet d'affecter un numero à chaque champion en prenant en
** compte les numeros transmis en parametre
*/

void				set_n_number(t_option *arg_data)
{
	long	id;
	int		i;

	id = 4294967295;
	i = -1;
	while (++i < arg_data->nb_champ)
	{
		if (arg_data->n[i] != 0)
			continue ;
		while (!check_id_is_available(id, arg_data->n, arg_data->nb_champ))
			id--;
		arg_data->n[i] = id--;
	}
}

/*
** get_data_of_champ recupere les information de header du champion
** actuellement traite.
** passe les valeurs magic et taille du programme de
** Big Endian vers Little Endian
*/

void				get_data_of_champ(t_header *header, const char src[])
{
	ft_memcpy(header, src, sizeof(*header));
	header->magic = unsigned_int_reverse_octet(header->magic);
	header->prog_size = unsigned_int_reverse_octet(header->prog_size);
}
