/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 11:47:10 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 17:39:25 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	debug(t_champ *champ)
{
	t_command	*command;
	int			i;
	
	command = champ->command_list;
	i = 0;
	printf("Dumping annotated program on standard output\n");
	printf("Program size : %d bytes\n", champ->program_size);
	if (strlen(champ->name) > PROG_NAME_LENGTH)
		printf("Name is too long !\n");
	else
		printf("Name : \"%s\"\n", champ->name);
	if (strlen(champ->comment) > COMMENT_LENGTH)
		printf("Comment is too long !\n");
	else
		printf("Comment : \"%s\"\n\n", champ->comment);
	while (command)
	{
		if (command->label)
		{
			printf("%-5d", command->index);
			printf("      :    %s:\n", command->label);
		}
		if (command->op)
		{
			printf("%-5d(%-3d) :", command->index, command->size);
			printf("\t%s", command->op);
			i = 0;
			while (command->params[i])
			{
				printf("\t%s (%d)", command->params[i]->value, command->params[i]->type);
				i++;
			}
			printf("\n\n");
		}
		command = command->next_command;
	}
}
