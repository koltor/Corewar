/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 13:06:57 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 18:14:03 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "asm.h"

void	check_format(int ac, char **av, t_data **data)
{
	int i;

	if (ac == 1)
		error_exit(USAGE);
	i = 1;
	while (i < ac)
	{
		if (!strcmp(av[i], "-a"))
			(*data)->annote = TRUE;
		else if (!((*data)->file_name = strdup(av[i])))
			error_exit("Malloc error !");
		i++;
	}
}

// void	generate_cor_file(t_champ *champ)
// {
// 	char *memory;

// 	memory = NULL;
// 	if (!(memory = (char *)malloc(PROG_NAME_LENGTH + COMMENT_LENGTH + 4 + champ->program_size)))
// 		error_exit("malloc error !");
// }

int		main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (!(data = new_data()))
		error_exit ("Malloc error !");
	check_format(ac, av, &data);
	if ((data->fd = open(data->file_name, O_RDONLY)) == -1)
		error_exit (strerror(errno));
	if (!(data->champ = new_champ()))
		error_exit ("Malloc error !");
	parse_file(data->fd, &(data->champ));
	compute_and_check(&(data->champ));
	// generate_cor_file(data->champ);
	debug(data->champ);
	exit(0);
}