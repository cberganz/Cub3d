/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 03:27:26 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/29 04:13:09 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_mouse(t_cub3d *cub3d)
{
	if (cub3d->mouse_set)
	{
		mlx_mouse_show(cub3d->mlx, cub3d->mlx_win);
		cub3d->mouse_set = 0;
	}
	else
	{
		mlx_mouse_hide(cub3d->mlx, cub3d->mlx_win);
		cub3d->mouse_set = 1;
	}
}
