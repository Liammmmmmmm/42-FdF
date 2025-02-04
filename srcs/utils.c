/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:51:55 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/04 15:11:33 by lilefebv         ###   ########lyon.fr   */
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

int	sitch_mode(int nb, int max)
{
	nb++;
	if (nb > max)
		return (0);
	return (nb);
}

int	get_biggest(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
