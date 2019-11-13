/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_struct.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 13:14:48 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 15:27:04 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

t_data		*new_data(void)
{
	t_data	*new_data;

	new_data = NULL;
	if (!(new_data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	ft_bzero(new_data, sizeof(t_data));
	return (new_data);
}

t_champ		*new_champ(void)
{
	t_champ	*new_champ;

	new_champ = NULL;
	if (!(new_champ = (t_champ *)malloc(sizeof(t_champ))))
		return (NULL);
	ft_bzero(new_champ, sizeof(t_champ));
	return (new_champ);
}

t_command	*new_op(void)
{
	t_command	*new_op;

	new_op = NULL;
	if (!(new_op = (t_command *)malloc(sizeof(t_command))))
		return (NULL);
	ft_bzero(new_op, sizeof(t_command));
	return (new_op);
}

t_param		**new_params(int param_count)
{
	t_param		**new_params;
	int			i;

	new_params = NULL;
	i = 0;
	if (!(new_params = (t_param **)malloc(sizeof(t_param *) *
		(param_count + 1))))
		return (NULL);
	ft_bzero(new_params, sizeof(t_param *) * (param_count + 1));
	while (i < param_count)
	{
		if (!(new_params[i] = (t_param *)malloc(sizeof(t_param))))
			return (NULL);
		ft_bzero(new_params[i], sizeof(t_param));
		i++;
	}
	return (new_params);
}
