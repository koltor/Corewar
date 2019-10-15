/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compute_champ.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 15:51:21 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/12 15:46:23 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	compute_command(t_command **command, t_champ *champ)
{
	int i;

	i = 0;
	(*command)->index = champ->program_size;
	if ((*command)->op)
	{
		(*command)->size = 1 + op_has_ocp((*command)->op);
		while ((*command)->params[i])
		{
			compute_param((*command)->params[i], champ, (*command));
			(*command)->size += (*command)->params[i]->size;
			(*command)->ocp += (*command)->params[i]->code;
			(*command)->ocp <<= 2;
			i++;
		}
		(*command)->ocp <<= 6 - (tab_length((void **)(*command)->params) * 2);
	}
}

void	compute_params_values(t_champ **champ)
{
	int			i;
	t_command	*curr_command;

	curr_command = (*champ)->command_list;
	while (curr_command)
	{
		if (curr_command->op)
		{
			i = 0;
			while (curr_command->params[i])
			{
				switch (curr_command->params[i]->type)
				{
					case T_REG:
						curr_command->params[i]->value = atoi(curr_command->params[i]->str + 1);
					break;
					case T_DIR:
						if (curr_command->params[i]->str[1] == LABEL_CHAR)
							curr_command->params[i]->value = label_index(curr_command->params[i]->str + 2, (*champ)) - curr_command->index;
						else
							curr_command->params[i]->value = atoi(curr_command->params[i]->str + 1);
					break;
					case T_IND:
						if (curr_command->params[i]->str[0] == LABEL_CHAR)
							curr_command->params[i]->value = label_index(curr_command->params[i]->str + 1, (*champ)) - curr_command->index;
						else
							curr_command->params[i]->value = atoi(curr_command->params[i]->str);
					break;
				}
				i++;
			}
		}
		curr_command = curr_command->next_command;
	}
}

void	compute_champ(t_champ **champ)
{
	t_command	*curr_command;

	curr_command = (*champ)->command_list;
	while (curr_command)
	{
		compute_command(&curr_command, *champ);
		(*champ)->program_size += curr_command->size;
		curr_command = curr_command->next_command;
	}
	compute_params_values(champ);
}