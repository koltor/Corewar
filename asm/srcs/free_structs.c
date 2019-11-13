/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_structs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/28 10:04:03 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 16:05:40 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	free_params(t_param **params)
{
	int i;

	i = 0;
	while (params[i])
	{
		if (params[i]->str)
			ft_strdel(&(params[i]->str));
		ft_bzero((void *)params[i], sizeof(t_param));
		ft_memdel((void **)&(params[i]));
		i++;
	}
}

static void	free_command(t_command *command)
{
	if (command->next_command)
		free_command(command->next_command);
	if (command->params)
		free_params(command->params);
	ft_memdel((void **)&(command->params));
	if (command->label)
		ft_strdel(&(command->label));
	if (command->op)
		ft_strdel(&(command->op));
	ft_bzero((void *)command, sizeof(t_command));
	ft_memdel((void **)&command);
}

static void	free_champ(t_champ *champ)
{
	t_command *command;

	command = NULL;
	if (champ->name)
		ft_strdel(&(champ->name));
	if (champ->comment)
		ft_strdel(&(champ->comment));
	if (champ->command_list)
		free_command(champ->command_list);
	ft_bzero((void *)champ, sizeof(t_champ));
	ft_memdel((void **)&champ);
}

void		free_data(t_data **data)
{
	if ((*data)->file_name)
		ft_strdel(&((*data)->file_name));
	if ((*data)->champ)
		free_champ((*data)->champ);
	if ((*data)->line)
		ft_strdel(&((*data)->line));
	ft_bzero((void *)*data, sizeof(t_data));
	ft_memdel((void **)data);
}
