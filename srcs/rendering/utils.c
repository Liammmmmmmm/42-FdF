/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:24:26 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/09 11:30:39 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_point_in_frame(t_point point)
{
	if (point.x < 0 || point.x >= WIN_WIDTH
		|| point.y < 0 || point.y >= WIN_HEIGHT)
		return (0);
	return (1);
}
