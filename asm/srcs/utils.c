/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/03 11:41:35 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/12 15:46:18 by kgrosjea    ###    #+. /#+    ###.fr     */
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
		if (curr_command->label && !strcmp(str, curr_command->label))
			return (TRUE);
		curr_command = curr_command->next_command;
	}
	return (FALSE);
}

int		label_index(char *label, t_champ *champ)
{
	t_command *command;

	command = champ->command_list;
	while (command)
	{
		if (command->label && !strcmp(label, command->label))
			return (command->index);
		command = command->next_command; 
	}
	return (0);
}

int		tab_length(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		error_exit(char *error_str)
{
	if (error_str)
		printf("%s\n", error_str);
	exit(1);
}

t_bool str_only_ctn(const char *str, const char *ctn)
{
	while (*str)
	{
		if (!ft_strctn(ctn, *str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

t_bool	ft_strctn(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (TRUE);
		str++;
	}
	return (FALSE);
}

int		count_char(const char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}