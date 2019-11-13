/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_to_cor.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 14:13:04 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 15:49:22 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	write_1_byte(int value, t_data *data)
{
	unsigned char uc;

	uc = 0;
	uc += value;
	if ((write(data->fd, &uc, 1)) == -1)
		error_exit(ft_sprintf("%s", strerror(errno)), &data);
}

static void	write_2_bytes(int value, t_data *data)
{
	unsigned short us;

	us = (unsigned short)value;
	us = unsigned_short_reverse_octet(us);
	if ((write(data->fd, &us, 2)) == -1)
		error_exit(ft_sprintf("%s", strerror(errno)), &data);
}

static void	write_4_bytes(int value, t_data *data)
{
	unsigned int ui;

	ui = 0;
	ui += value;
	ui = unsigned_int_reverse_octet(ui);
	if ((write(data->fd, &ui, 4)) == -1)
		error_exit(ft_sprintf("%s", strerror(errno)), &data);
}

void		write_header(t_data *data)
{
	size_t		i;
	t_header	header;

	i = 0;
	ft_bzero(&header, sizeof(t_header));
	header.magic = unsigned_int_reverse_octet(COREWAR_EXEC_MAGIC);
	header.prog_size = unsigned_int_reverse_octet(data->champ->program_size);
	while (i < PROG_NAME_LENGTH && i < ft_strlen(data->champ->name))
	{
		header.prog_name[i] = data->champ->name[i];
		i++;
	}
	i = 0;
	while (i < COMMENT_LENGTH && i < ft_strlen(data->champ->comment))
	{
		header.comment[i] = data->champ->comment[i];
		i++;
	}
	if ((write(data->fd, &header, sizeof(t_header))) == -1)
		error_exit(ft_sprintf("%s", strerror(errno)), &data);
}

void		write_command(t_data *data, t_command *command)
{
	int i;

	i = 0;
	write_1_byte(op_code(command->op), data);
	if (op_has_ocp(command->op))
		write_1_byte(command->ocp, data);
	while (command->params[i])
	{
		if (command->params[i]->size == 1)
			write_1_byte(command->params[i]->value, data);
		else if (command->params[i]->size == 2)
			write_2_bytes(command->params[i]->value, data);
		else if (command->params[i]->size == 4)
			write_4_bytes(command->params[i]->value, data);
		i++;
	}
}
