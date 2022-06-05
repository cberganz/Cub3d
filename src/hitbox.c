/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:46:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 19:49:15 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint8_t	hitbox_wallhit(t_cub3d *cub3d, double x, double y)
{	
	return (cub3d->map_struct.map_strs[(int)y][(int)(x + HITBOX_SIZE)] == '0'
		&& cub3d->map_struct.map_strs[(int)y][(int)(x - HITBOX_SIZE)] == '0'
		&& cub3d->map_struct.map_strs[(int)(y + HITBOX_SIZE)][(int)x] == '0'
		&& cub3d->map_struct.map_strs[(int)(y - HITBOX_SIZE)][(int)x] == '0');
}

uint8_t	is_on_door(t_cub3d *cub3d, t_door *targeted_door)
{
	return (((int)targeted_door->x == (int)(cub3d->player.posX + HITBOX_SIZE)
		&& (int)targeted_door->y == (int)cub3d->player.posY)
		|| ((int)targeted_door->x == (int)(cub3d->player.posX - HITBOX_SIZE)
		&& (int)targeted_door->y == (int)cub3d->player.posY)
		|| ((int)targeted_door->x == (int)cub3d->player.posX
		&& (int)targeted_door->y == (int)(cub3d->player.posY + HITBOX_SIZE))
		|| ((int)targeted_door->x == (int)cub3d->player.posX
		&& (int)targeted_door->y == (int)(cub3d->player.posY - HITBOX_SIZE)));
}
