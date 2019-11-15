/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_min.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/07 18:08:25 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 14:52:07 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_min(int nb1, int nb2)
{
	return (nb1 >= nb2 ? nb2 : nb1);
}