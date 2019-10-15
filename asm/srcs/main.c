/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 13:06:57 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 17:18:51 by kgrosjea    ###    #+. /#+    ###.fr     */
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
			error_exit(strerror(errno));
		i++;
	}
}

int		open_cor_file(char *file_name)
{
	int		fd;
	char	*cor_file_name;

	fd = 0;
	cor_file_name = ft_strsub(file_name, 0, strlen(file_name) - 2);
	cor_file_name = strcat(cor_file_name, ".cor");
	if ((fd = open(cor_file_name, O_CREAT|O_WRONLY, 0777)) == -1)
		error_exit(strerror(errno));
	return (fd);
}

void	write_cor_file(int fd, t_champ *champ)
{
	t_command	*command;

	command = champ->command_list;
	write_header(fd, champ);
	while (command)
	{
		if (command->op)
			write_command(fd, command);
		command = command->next_command;
	}
}

// void	debug(t_champ *champ)
// {
// 	int i;
// 	t_command *command;

// 	command = champ->command_list;
// 	printf("Name: \"%s\"\n", champ->name);
// 	printf("Comment: \"%s\"\n", champ->comment);
// 	while (command)
// 	{
// 		i = 0;
// 		if (command->label)
// 			printf("%s:\n", command->label);
// 		if (command->op)
// 		{
// 			printf("%s", command->op);
// 			while (command->params[i])
// 			{
// 				printf("\t%s (%x)", command->params[i]->str, command->params[i]->value);
// 				i++;
// 			}
// 		}
// 		printf("\n\n");
// 		command = command->next_command;
// 	}
// }

int		main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (!(data = new_data()))
		error_exit (strerror(errno));
	check_format(ac, av, &data);
	if ((data->fd = open(data->file_name, O_RDONLY)) == -1)
		error_exit (strerror(errno));
	if (!(data->champ = new_champ()))
		error_exit (strerror(errno));
	parse_file(data->fd, &(data->champ));
	compute_champ(&(data->champ));
	// debug(data->champ);
	write_cor_file(open_cor_file(data->file_name), data->champ);
	exit(0);
}