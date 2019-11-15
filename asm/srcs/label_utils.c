/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   label_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 17:41:54 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 12:49:15 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

t_bool	label_exists(char *str, t_command *command_list)
{
	t_command *curr_command;

	curr_command = command_list;
	while (curr_command)
	{
		if (curr_command->label && !ft_strcmp(str, curr_command->label))
			return (TRUE);
		curr_command = curr_command->next_command;
	}
	return (FALSE);
}

int		label_index(char *label, t_data **data)
{
	t_command *command;

	command = (*data)->champ->command_list;
	while (command)
	{
		if (command->label && !ft_strcmp(label, command->label))
			return (command->index);
		command = command->next_command;
	}
	error_exit(ft_sprintf("No such label %s", label), data);
	return (0);
}
