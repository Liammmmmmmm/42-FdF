/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:51:55 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/13 16:49:18 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	flip_flop(int nb)
{
	if (nb == 0)
		return (1);
	else
		return (0);
}

int	get_biggest(int a, int b)
{
	if (a > b)
		return a;
	return (b);
}
