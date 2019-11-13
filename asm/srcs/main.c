/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 13:06:57 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 14:40:06 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void		check_format(int ac, char **av, t_data **data)
{
	int i;

	i = 1;
	if (ac == 1)
		error_exit(ft_sprintf("%s%s%s\n", USAGE_1, USAGE_2, USAGE_3), data);
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-a") && !((*data)->file_name = ft_strdup(av[i])))
			error_exit(ft_sprintf("%s", strerror(errno)), data);
		i++;
	}
}

static void		open_cor_file(t_data **data)
{
	int		fd;
	char	*cor_file_name;

	fd = 0;
	cor_file_name = ft_strsub((*data)->file_name, 0,
					ft_strlen((*data)->file_name) - 2);
	cor_file_name = ft_strjoin_f(cor_file_name, ".cor", 1);
	if (((*data)->fd = open(cor_file_name, O_CREAT | O_WRONLY, 0777)) == -1)
	{
		ft_strdel(&cor_file_name);
		error_exit(ft_sprintf("%s", strerror(errno)), data);
	}
	ft_printf("Writing output program to %s\n", cor_file_name);
	ft_strdel(&cor_file_name);
}

static void		write_cor_file(t_data *data)
{
	t_command	*command;

	command = data->champ->command_list;
	if (!data->champ->name && !data->champ->comment &&
		!data->champ->command_list)
		error_exit(ft_sprintf("%s", ft_sprintf("File is empty")), &data);
	write_header(data);
	while (command)
	{
		if (command->op)
			write_command(data, command);
		command = command->next_command;
	}
}

static void		parse_file(t_data **data)
{
	while (get_next_line((*data)->fd, &((*data)->line)) > 0)
	{
		parse_line(data);
		ft_strdel(&((*data)->line));
	}
	get_next_line(-42, NULL);
	if (close((*data)->fd) != 0)
		error_exit(ft_sprintf("%s", strerror(errno)), data);
}

int				main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (!(data = new_data()))
		error_exit(ft_sprintf("%s", strerror(errno)), &data);
	check_format(ac, av, &data);
	if ((data->fd = open(data->file_name, O_RDONLY)) == -1)
		error_exit(ft_sprintf("%s", strerror(errno)), &data);
	if (!(data->champ = new_champ()))
		error_exit(ft_sprintf("%s", strerror(errno)), &data);
	parse_file(&data);
	compute_champ(&data);
	open_cor_file(&data);
	write_cor_file(data);
	free_data(&data);
	exit(0);
}
