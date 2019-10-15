/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compute_param.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 15:51:33 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/12 14:48:37 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	set_reg_param(t_param **param)
{
	(*param)->type = T_REG;
	(*param)->code = REG_CODE;
	(*param)->size = 1;
}

static void	set_dir_param(t_param **param, t_champ *champ, t_command *command)
{
	if (((*param)->str[1] == LABEL_CHAR && label_exists((*param)->str + 2, champ->command_list)) ||
		str_only_ctn((*param)->str + 1, "-0123456789"))
	{
		(*param)->type = T_DIR;
		(*param)->code = DIR_CODE;
		(*param)->size = op_dir_size(command->op) ? 2 : 4;
	}
	else
	{
		printf("%s\n", (*param)->str);
		error_exit("Invalid param");
	}
}

static void	set_ind_param(t_param **param)
{
	(*param)->type = T_IND;
	(*param)->code = IND_CODE;
	(*param)->size = 2;
}

void		compute_param(t_param *param, t_champ *champ, t_command *command)
{
	if (param->str[0] == 'r' && str_only_ctn(param->str + 1, "0123456789"))
		set_reg_param(&param);
	else if (param->str[0] == DIRECT_CHAR)
		set_dir_param(&param, champ, command);
	else
		set_ind_param(&param);
}