/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_champ.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 10:12:48 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 13:14:53 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** close_file permet de fermer tous les fichier ouverts a la fin du parsing peut
** importe le resultat
*/

static int			close_file(int nbfile, int files[MAX_PLAYERS])
{
	int i;

	i = -1;
	while (++i < nbfile)
	{
		if (files[i] != -1)
			close(files[i]);
	}
	return (0);
}

/*
** put_champ_on_arena place les differents champions qu'on lui envois
** le placement des champions depend du nombre de champion envoyés
** et de combien de champion il à déjà placé au prealable
*/

static void			put_champ_on_arena(int n_champ, char arena[], const char champ[], int nb_champs, int champ_size)
{
    float section;
    int     i;

	if (nb_champs != 0)
    	section = MEM_SIZE / nb_champs;
	else
		section = MEM_SIZE;
    if (section - (int)section > 0.5)
        section = section + 1.0;
    i = n_champ * (int)section;
    ft_memcpy(&arena[i], &champ[16 + PROG_NAME_LENGTH + COMMENT_LENGTH], champ_size);
}

/*
** check_data_of_champ verifie les informations d'header contunu dans le champion
** et renvoie 0 en cas d'erreur dans le header.
** il verifie également la correspondance de la taille du programme avec le programme
** transmis.
*/

int					check_data_of_champ(t_header header, int file_len)
{
	if (header.magic != COREWAR_EXEC_MAGIC)
		return (0);
	if (header.prog_size > CHAMP_MAX_SIZE)
		return (0);
	if (header.prog_size != file_len - ( 16 + PROG_NAME_LENGTH + COMMENT_LENGTH))
		return (0);
	return (1);
}

/*
** process_arg_cycle traite les champions 1 par 1 jusqu'au dernier
** et remplies la base de donnée des champions
** et les places sur l'arene equitablement.
*/

void				process_champ(t_option arg_data, t_header (*header)[MAX_PLAYERS], char *arena)
{
	char buff[CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH];
	int file_len;
	int i;

	i = -1;
	while (++i < arg_data.nb_champ)
	{
		file_len = read(arg_data.fd[i], &buff, CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH);
		get_data_of_champ(&(*header)[i], buff);
		if (!check_data_of_champ((*header)[i], file_len))
			break ;
		put_champ_on_arena(i, arena, buff, arg_data.nb_champ, (*header)[i].prog_size);
	}
	close_file(arg_data.nb_champ, arg_data.fd);
	if (i < arg_data.nb_champ)
		invalid_champs();
}
