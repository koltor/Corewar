/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compute_champ.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 15:51:21 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 17:28:31 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	compute_command(t_command **command, t_data **data)
{
	int i;

	i = 0;
	(*command)->index = (*data)->champ->program_size;
	if ((*command)->op)
	{
		(*command)->size = 1 + op_has_ocp((*command)->op);
		while ((*command)->params[i])
		{
			compute_param((*command)->params[i], data, (*command), i);
			(*command)->size += (*command)->params[i]->size;
			(*command)->ocp += (*command)->params[i]->code;
			(*command)->ocp <<= 2;
			i++;
		}
		(*command)->ocp <<= 6 - (tab_length((void **)(*command)->params) * 2);
	}
}

static void	compute_dir_value(t_data **data, t_command **command, int i)
{
	if ((*command)->params[i]->str[1] == LABEL_CHAR)
		(*command)->params[i]->value =
		label_index((*command)->params[i]->str + 2, data) - (*command)->index;
	else
		(*command)->params[i]->value = ft_atoi((*command)->params[i]->str + 1);
}

static void	compute_ind_value(t_data **data, t_command **command, int i)
{
	if ((*command)->params[i]->str[0] == LABEL_CHAR)
		(*command)->params[i]->value =
		label_index((*command)->params[i]->str + 1, data) - (*command)->index;
	else
		(*command)->params[i]->value = ft_atoi((*command)->params[i]->str);
}

static void	compute_params_values(t_data **data)
{
	int			i;
	t_command	*curr_command;

	curr_command = (*data)->champ->command_list;
	while (curr_command)
	{
		if (curr_command->op)
		{
			i = 0;
			while (curr_command->params[i])
			{
				if (curr_command->params[i]->type == T_REG)
					curr_command->params[i]->value =
					ft_atoi(curr_command->params[i]->str + 1);
				else if (curr_command->params[i]->type == T_DIR)
					compute_dir_value(data, &curr_command, i);
				else if (curr_command->params[i]->type == T_IND)
					compute_ind_value(data, &curr_command, i);
				i++;
			}
		}
		curr_command = curr_command->next_command;
	}
}

void		compute_champ(t_data **data)
{
	t_command	*curr_command;

	curr_command = (*data)->champ->command_list;
	while (curr_command)
	{
		compute_command(&curr_command, data);
		(*data)->champ->program_size += curr_command->size;
		curr_command = curr_command->next_command;
	}
	compute_params_values(data);
}
