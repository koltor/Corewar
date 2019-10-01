/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_arg.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 07:52:33 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/30 12:47:27 by matheme     ###    #+. /#+    ###.fr     */
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
	while (++i < nbfile)
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

static int	check_error_arg(t_option arg_data)
{
	int i;

	i = -1;
	if (arg_data.dump == -1 || arg_data.option == -1 || arg_data.expected_arg != 0)
		return (close_file(arg_data.nb_champ, arg_data.fd));
	if (arg_data.nb_champ > MAX_PLAYERS)
		return (close_file(arg_data.nb_champ, arg_data.fd));
	while (++i < arg_data.nb_champ)
		if (arg_data.fd[i] == -1 || arg_data.n[i] == -1)
			return (close_file(arg_data.nb_champ, arg_data.fd));
	if (i == 0)
		return (close_file(arg_data.nb_champ, arg_data.fd));
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
	if (expected_arg == 0)
	{
		if (str[0] == '-')
			return (RECUPERE_OPTIONS);
		return (OUVRE_UN_FICHIER);
	}
	if (expected_arg == 1 || expected_arg == 2)
		return (RECUPERE_VALEURS);
	return (OUVRE_UN_FICHIER);
}

/*
** treat_arg reçois un code d'instruction et execute la fonction associer
** en lui transmettant les arguments attendu par la fonction
** code d'instruction 0: ouvrir un fichier champion
** code d'instruction 1: recuperer un ou des options;
** code d'instruction 2: recuperer une valeur pour le dump ou le champion
**          (execute un atol et verifie les overflows pour int)
*/

static void	treat_arg(char n, char *str, t_option *arg_data)
{
	static void	(*p[3])(char*, t_option*) = {
		&get_champ, &get_option, &get_value_for
	};

	p[n](str, arg_data);
}

/*
** process_arg_cycle traite les arguments 1 par 1 jusqu'au dernier
** et remplies la base de donnée des arguments
*/

static void	process_arg_cycle(t_option *arg_data, int ac, char **av)
{
	char instruct_code;

	instruct_code = 0;
	if (ac == 0)
		return ;
	instruct_code = get_instruct_code(arg_data->expected_arg, av[0]);
	treat_arg(instruct_code, av[0], arg_data);
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
	process_arg_cycle(arg_data, ac, av);
	if (!check_error_arg(*arg_data))
		usage();
}
