/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 03:27:26 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/28 03:43:56 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    mouse_rotation(t_cub3d *cub3d)
{
    int     x;
    int     y;
    int     x_dist;

    mlx_mouse_get_pos(cub3d->mlx, cub3d->mlx_win, &x, &y);
    x_dist = x - (SCREEN_WIDTH / 2);
	if (x_dist > 0)
		cub3d->p_angle -= VISION_MOVE_PER_FRAME * x_dist;
	else if (x_dist < 0)
		cub3d->p_angle += VISION_MOVE_PER_FRAME * -x_dist;
	if (cub3d->p_angle > 360)
		cub3d->p_angle -= 360;
	else if (cub3d->p_angle < 0)
		cub3d->p_angle += 360;
}
