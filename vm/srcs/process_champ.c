/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_champ.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 10:12:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 18:44:35 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** close_file permet de fermer tous les fichier ouverts a la fin du parsing peut
** importe le resultat
*/

static void	close_file(int nbfile, int files[MAX_PLAYERS], int err)
{
	int i;

	i = -1;
	while (++i < nbfile)
	{
		if (files[i] != -1)
			close(files[i]);
	}
	if (err)
		f_error(err);
}

static int	get_pos_of_champs_arena(int n_champ, int nb_champs)
{
	float	section;

	if (nb_champs != 0)
		section = MEM_SIZE / nb_champs;
	else
		section = MEM_SIZE;
	if (section - (int)section > 0.5)
		section = section + 1.0;
	return (n_champ * (int)section);
}

/*
** put_champ_on_arena place les differents champions qu'on lui envois
** le placement des champions depend du nombre de champion envoyés
** et de combien de champion il à déjà placé au prealable
*/

static void	put_champ_on_arena(int p, char arna[], const char ch[], int ch_size)
{
	ft_memcpy(&arna[p], &ch[16 + PROG_NAME_LENGTH + COMMENT_LENGTH], ch_size);
}

/*
** check_data_of_champ verifie les informations header contunu dans le champion
** et renvoie 0 en cas d'erreur dans le header.
** il verifie également la correspondance de la taille du programme avec
** le programme transmis.
*/

static int	check_data_of_champ(t_header header, int file_len)
{
	if (header.magic != COREWAR_EXEC_MAGIC)
		return (ERR_FILE_MAGIC);
	if (header.prog_size > CHAMP_MAX_SIZE)
		return (ERR_FILE_SIZE);
	if (header.prog_size !=
		(unsigned int)(file_len - 16 - PROG_NAME_LENGTH - COMMENT_LENGTH))
		return (ERR_FILE_CORRUPT);
	return (0);
}

/*
** process_arg_cycle traite les champions 1 par 1 jusqu'au dernier
** et remplies la base de donnée des champions
** et les places sur l'arene equitablement.
*/

void		process_champ(t_option *arg_data, t_header (*header)[], char *arena)
{
	char	buff[CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 20];
	int		file_len;
	int		i;
	int		err;
	int		pos_champ;

	i = -1;
	while (++i < arg_data->nb_champ)
	{
		file_len = read(arg_data->fd[i], &buff,
				CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 20);
		get_data_of_champ(&(*header)[i], buff);
		if ((err = check_data_of_champ((*header)[i], file_len)))
			close_file(arg_data->nb_champ, arg_data->fd, err);
		pos_champ = get_pos_of_champs_arena(i, arg_data->nb_champ);
		put_champ_on_arena(pos_champ, arena, buff, (*header)[i].prog_size);
	}
	set_n_number(arg_data);
	close_file(arg_data->nb_champ, arg_data->fd, 0);
}
