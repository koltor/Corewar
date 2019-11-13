/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 18:19:38 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 16:44:37 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

t_command	*last_command(t_champ **champ)
{
	t_command	*curr_command;

	curr_command = NULL;
	if (!(*champ)->command_list)
	{
		if (!((*champ)->command_list = (t_command *)malloc(sizeof(t_command))))
			return (NULL);
		bzero((*champ)->command_list, sizeof(t_command));
		curr_command = (*champ)->command_list;
	}
	else
	{
		curr_command = (*champ)->command_list;
		while (curr_command->next_command)
			curr_command = curr_command->next_command;
	}
	return (curr_command);
}

t_command	*next_command(t_command **curr_command)
{
	if (!(*curr_command)->next_command)
	{
		if (!((*curr_command)->next_command =
		(t_command *)malloc(sizeof(t_command))))
			return (NULL);
		bzero((*curr_command)->next_command, sizeof(t_command));
	}
	return ((*curr_command)->next_command);
}
