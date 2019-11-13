/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_arg.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 07:52:33 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 18:42:41 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
** close_file permet de fermer tous les fichier ouverts lors du parsing en cas
** d'erreur.
*/

static int	close_file(int nbfile, int files[MAX_PLAYERS])
{
	int i;

	i = -1;
	while (++i < nbfile && i < MAX_PLAYERS)
	{
		if (files[i] != -1)
			close(files[i]);
	}
	return (0);
}

/*
** check_error_arg scan la structure arg_data a la recherche d'erreur eventuel
** lors du parsing.
*/

static int	check_error_arg(t_option arg_da)
{
	int i;

	i = -1;
	if (arg_da.dump == -2 || arg_da.expected_arg != 0 || arg_da.verbose == -2)
		return (close_file(arg_da.nb_champ, arg_da.fd));
	if (arg_da.nb_champ > MAX_PLAYERS)
		return (close_file(arg_da.nb_champ, arg_da.fd));
	while (++i < arg_da.nb_champ)
		if (arg_da.fd[i] == -1)
			return (close_file(arg_da.nb_champ, arg_da.fd));
	if (i == 0)
		return (close_file(arg_da.nb_champ, arg_da.fd));
	return (1);
}

/*
** get_instruct_code reçois la valeur du code d'instruction attendu et regarde
** l'argument passé en parametre.
** La fonction renvoie la nouvelle valeur d'instruction en fonction du parametre
** expected_arg 0: soit option soit champion
** expected_arg 1: valeur pour n
** expected_arg 2: valeur pour dump
** expected_arg 3: valeur champion obligatoire
*/

static char	get_instruct_code(char expected_arg, char *str)
{
	if (expected_arg == -1)
		return (INSTRUCT_CODE_ERROR);
	if (expected_arg == 0)
	{
		if (str[0] == '-')
			return (RECUPERE_OPTIONS);
		return (OUVRE_UN_FICHIER);
	}
	if (expected_arg == 1 || expected_arg == 2 || expected_arg == 3)
	{
		if (((*str < '0' || *str > '9') && *str != '+') || *str == '-')
			return (INSTRUCT_CODE_ERROR);
		return (RECUPERE_VALEURS);
	}
	return (OUVRE_UN_FICHIER);
}

/*
** process_arg_cycle traite les arguments 1 par 1 jusqu'au dernier
** et remplies la base de donnée des arguments
** la fonction genere egalement un code d'instruction et execute
** la fonction associer
** en lui transmettant les arguments attendu par la fonction
** code d'instruction 0: ouvrir un fichier champion
** code d'instruction 1: recuperer un ou des options;
** code d'instruction 2: recuperer une valeur pour le dump ou le champion
**          (execute un atol et verifie les overflows pour int)
*/

static void	process_arg_cycle(t_option *arg_data, int ac, char **av)
{
	int			instruct_code;
	static void	(*p[3])(char*, t_option*) = {
		&get_champ, &get_option, &get_value_for
	};

	instruct_code = 0;
	if (ac == 0)
		return ;
	instruct_code = get_instruct_code(arg_data->expected_arg, av[0]);
	if (instruct_code == INSTRUCT_CODE_ERROR)
		return ;
	p[instruct_code](av[0], arg_data);
	process_arg_cycle(arg_data, ac - 1, &av[1]);
}

/*
** process_arg execute la fonction process_arg_cycle
** et verifie les donnée enregistrer.
** si une erreur est detecté.
** envoie l'usage directement
*/

void		process_arg(t_option *arg_data, int ac, char **av)
{
	int i;

	i = 0;
	ft_bzero(arg_data, sizeof(t_option));
	arg_data->dump = -1;
	arg_data->verbose = -1;
	while (i < MAX_PLAYERS)
		arg_data->n[i++] = 0;
	process_arg_cycle(arg_data, ac, av);
	if (!check_error_arg(*arg_data))
		usage();
}
