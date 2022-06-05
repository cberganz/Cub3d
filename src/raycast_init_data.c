/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:03:44 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 19:05:07 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	conditional_inizialize(t_cub3d *cub3d, t_raycast *raycast)
{
	if (raycast->rayDirX < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (cub3d->player.posX - raycast->mapX)
			* raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->mapX + 1.0 - cub3d->player.posX)
			* raycast->deltaDistX;
	}
	if (raycast->rayDirY < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (cub3d->player.posY - raycast->mapY)
			* raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->mapY + 1.0 - cub3d->player.posY)
			* raycast->deltaDistY;
	}
}

void	raycast_initialize(t_cub3d *cub3d, t_raycast *raycast, int x)
{
	raycast->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
	raycast->rayDirX = cub3d->player.dirX + raycast->planeX * raycast->cameraX;
	raycast->rayDirY = cub3d->player.dirY + raycast->planeY * raycast->cameraX;
	raycast->mapX = (int)cub3d->player.posX;
	raycast->mapY = (int)cub3d->player.posY;
	raycast->deltaDistX = 1e30;
	raycast->deltaDistY = 1e30;
	raycast->hit = 0;
	if (raycast->rayDirX != 0)
		raycast->deltaDistX = fabs(1 / raycast->rayDirX);
	if (raycast->rayDirY != 0)
		raycast->deltaDistY = fabs(1 / raycast->rayDirY);
	conditional_inizialize(cub3d, raycast);
}

void	raycast_find_wall(t_cub3d *cub3d, t_raycast *raycast, int do_hit_door)
{
	while (raycast->hit == 0)
	{
		if (raycast->sideDistX < raycast->sideDistY)
		{
			raycast->sideDistX += raycast->deltaDistX;
			raycast->mapX += raycast->stepX;
			raycast->side = 0;
		}
		else
		{
			raycast->sideDistY += raycast->deltaDistY;
			raycast->mapY += raycast->stepY;
			raycast->side = 1;
		}
		if (cub3d->map_struct.map_strs[raycast->mapY][raycast->mapX] == '1'
			|| (do_hit_door == 1
			&& cub3d->map_struct.map_strs[raycast->mapY][raycast->mapX] == 'D'))
			raycast->hit = 1;
	}
	if (raycast->side == 0)
		raycast->perpWallDist = (raycast->sideDistX - raycast->deltaDistX);
	else
		raycast->perpWallDist = (raycast->sideDistY - raycast->deltaDistY);
}

void	find_texture_index(t_cub3d *cub3d)
{
	if (cub3d->map_struct
		.map_strs[cub3d->raycast.mapY][cub3d->raycast.mapX] == 'D')
		cub3d->raycast.texNum = 4;
	else if (cub3d->raycast.side == 1)
	{
		if (cub3d->raycast.rayDirY >= 0)
			cub3d->raycast.texNum = 0;
		else
			cub3d->raycast.texNum = 1;
	}
	else
	{
		if (cub3d->raycast.rayDirX >= 0)
			cub3d->raycast.texNum = 2;
		else
			cub3d->raycast.texNum = 3;
	}
}

void	texture_calculation(t_cub3d *cub3d)
{
	find_texture_index(cub3d);
	if (cub3d->raycast.side == 0)
	{
		cub3d->raycast.wallX = cub3d->player.posY + cub3d->raycast.perpWallDist
			* cub3d->raycast.rayDirY;
	}
	else
	{
		cub3d->raycast.wallX = cub3d->player.posX + cub3d->raycast.perpWallDist
			* cub3d->raycast.rayDirX;
	}
	cub3d->raycast.wallX -= floor((cub3d->raycast.wallX));
	cub3d->raycast.texX = (int)(cub3d->raycast.wallX
			* (double)cub3d->sprites[cub3d->raycast.texNum].x);
	if (cub3d->raycast.side == 0 && cub3d->raycast.rayDirX > 0)
		cub3d->raycast.texX = cub3d->sprites[cub3d->raycast.texNum].x
			- cub3d->raycast.texX - 1;
	if (cub3d->raycast.side == 1 && cub3d->raycast.rayDirY < 0)
		cub3d->raycast.texX = cub3d->sprites[cub3d->raycast.texNum].x
			- cub3d->raycast.texX - 1;
}
