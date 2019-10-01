/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_arg_sf.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/27 13:28:58 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/30 10:38:41 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** get_value_for reçois l'argument actuel à traiter et la traite comme étant
** unt nombre.
** la fonction verifie le max && min int et stock la valeur au bonne endroit
** dans la struct arg_data.
** modifie: l'expected_arg
*/

void		get_value_for(char *str, t_option *arg_data)
{
	long	value;
	int		i;

	i = -1;
	value = ft_atol(str);
	if (value < -2147483648 || value > 2147483647 || value == 0)
		value = -1;
	if (arg_data->expected_arg == 1)
	{
		if (arg_data->nb_champ >= MAX_PLAYERS)
		{
			arg_data->expected_arg = 3;
			return ;
		}
		while (++i < MAX_PLAYERS)
			if (value == arg_data->n[i])
				value = -1;
		arg_data->n[arg_data->nb_champ] = value;
		arg_data->expected_arg = 3;
	}
	else
	{
		arg_data->dump = value;
		arg_data->expected_arg = 0;
	}
}

/*
** liste des options traiter
** pour rajouter une option il suffit de recopier le patern suivant
** modifie: l'expected_arg
** modifie: option
*/

static int	ft_listing_option(char c, int option, char *expected_arg)
{
	c == 'v' ? option = option | +2 : 0;
	c == 'd' ? option = option | +1 : 0;
	c == 'd' ? *expected_arg = 2 : 0;
	c == 'n' ? *expected_arg = 1 : 0;
	return (option);
}

/*
** get_option reçois l'argument actuel à traiter et la traite comme étant
** une option ou des options.
** avance dans la string tant que expected_arg est egal à 0 et que les differentes
** options sont connus
*/

void		get_option(char *str, t_option *arg_data)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr(LIST_OPTION, str[i]) == NULL || arg_data->expected_arg != 0)
		{
			arg_data->option = -1;
			break ;
		}
		arg_data->option = ft_listing_option(str[i], arg_data->option, &arg_data->expected_arg);
		i++;
	}
}

/*
** check_champ_path
** verifie que le nom du fichier se termine bien par .cor
*/

static int	check_champ_path(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	if (i <= 4)
		return (0);
	i--;
	if (s[i] != 'r' || s[i - 1] != 'o' || s[i - 2] != 'c' || s[i - 3] != '.')
		return (0);
	return (1);
}

/*
** get_champ eçois l'argument actuel à traiter et la traite comme étant
** un fichier de champion.
** verifie la validiter du fichier (ouverture/lecture)
** et le stock au bonne endroit dans la structure arg_data
** modifie: l'expected_arg
** augmente le nombre de champion de +1
*/

void		get_champ(char *champ_path, t_option *arg_data)
{
	if (!check_champ_path(champ_path))
	{
		arg_data->fd[arg_data->nb_champ] = -1;
		arg_data->nb_champ += 1;
		return ;
	}
	if (arg_data->nb_champ >= MAX_PLAYERS)
	{
		arg_data->nb_champ += 1;
		arg_data->expected_arg = 0;
		return ;
	}
	arg_data->fd[arg_data->nb_champ] = open(champ_path, O_RDONLY);
	if (read(arg_data->fd[arg_data->nb_champ], NULL, 0) < 0)
	{
		close(arg_data->fd[arg_data->nb_champ]);
		arg_data->fd[arg_data->nb_champ] = -1;
	}
	arg_data->nb_champ += 1;
	arg_data->expected_arg = 0;
}
