/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compute_and_check.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 17:30:01 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 17:38:09 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static t_bool	label_exists(char *str, t_command *command_list)
{
	t_command *curr_command;

	curr_command = command_list;
	while (curr_command)
	{
		if (curr_command->label && !strcmp(str, curr_command->label))
			return (TRUE);
		curr_command = curr_command->next_command;
	}
	return (FALSE);
}

static int		check_param(char *str, t_command *command_list, char *op)
{
	if (*str == 'r' && atoi(str + 1) <= REG_NUMBER && atoi(str + 1) > 0)
		return (T_REG);
	else if (*str == DIRECT_CHAR)
	{
		if (*(str + 1) == LABEL_CHAR)
		{
			if (label_exists(str + 2, command_list))
				return (op_dir_size(op) ? T_DIR : T_IND);
		}
		else if (str_only_ctn(str + 1, "+-0123456789"))
			return (op_dir_size(op) ? T_DIR : T_IND);
	}
	else if (str_only_ctn(str, "+-0123456789"))
		return (T_DIR);
	return (0);
}

void	compute_and_check(t_champ **champ)
{
	t_command	*curr_command;
	int			i;

	curr_command = (*champ)->command_list;
	i = 0;
	while (curr_command)
	{
		if (curr_command->op)
		{
			curr_command->size = 1 + op_has_ocp(curr_command->op);
			i = 0;
			while (curr_command->params[i])
			{
				if (!(curr_command->params[i]->type = check_param(curr_command->params[i]->value, (*champ)->command_list, curr_command->op)))
					error_exit ("Param error !");
				curr_command->size += curr_command->params[i]->type;
				i++;
			}
		}
		curr_command->index = (*champ)->program_size;
		(*champ)->program_size += curr_command->size;
		curr_command = curr_command->next_command;
	}
}