/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_to_cor.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 14:13:04 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 17:18:44 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	write_header(int fd, t_champ *champ)
{
	size_t		i;
	t_header	header;
	
	i = 0;
	ft_bzero(&header, sizeof(t_header));
	header.magic = unsigned_int_reverse_octet(COREWAR_EXEC_MAGIC);
	header.prog_size = unsigned_int_reverse_octet(champ->program_size);
	while(i < PROG_NAME_LENGTH && i < strlen(champ->name))
	{
		header.prog_name[i] = champ->name[i];
		i++;
	}
	i = 0;
	while(i < COMMENT_LENGTH && i < strlen(champ->comment))
	{
		header.comment[i] = champ->comment[i];
		i++;
	}
	if ((write(fd, &header, sizeof(t_header))) == -1)
		error_exit(strerror(errno));
}

void	write_command(int fd, t_command *command)
{
	int i;

	i = 0;
	write_1_byte(op_code(command->op), fd);
	if (op_has_ocp(command->op))
		write_1_byte(command->ocp, fd);
	while(command->params[i])
	{
		switch(command->params[i]->size)
		{
			case 1:
				write_1_byte(command->params[i]->value, fd);
			break;
			case 2:
				write_2_bytes(command->params[i]->value, fd);
			break;
			case 4:
				write_4_bytes(command->params[i]->value, fd);
			break;
			default:
			break;
		}
		i++;
	}
}

void	write_1_byte(int value, int fd)
{
	unsigned char uc;

	uc = 0;
	uc += value;
	if ((write(fd, &uc, 1)) == -1)
		error_exit(strerror(errno));
}

void	write_2_bytes(int value, int fd)
{
	unsigned short us;

	us = 0;
	us += value;
	us = unsigned_short_reverse_octet(us);
	if ((write(fd, &us, 2)) == -1)
		error_exit(strerror(errno));
}

void	write_4_bytes(int value, int fd)
{
	unsigned int ui;

	ui = 0;
	ui += value;
	ui = unsigned_int_reverse_octet(ui);
	if ((write(fd, &ui, 4)) == -1)
		error_exit(strerror(errno));
}