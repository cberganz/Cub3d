/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 00:01:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/29 17:04:10 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_to_img(t_tex *img, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	*(int *)(img->addr + ((x + y * SCREEN_WIDTH) * img->bpp)) = color;
}

static void draw_line(t_cub3d *cub3d, int x)
{
    int i;

    i = 0;
    while (i < SCREEN_HEIGHT)
    {
        if (i < cub3d->raycast.drawStart)
            put_pixel_to_img(&cub3d->raycast_img, x, i, cub3d->colors.sky);
        else if (i < cub3d->raycast.drawEnd)
        {
            if (cub3d->raycast.side)
                put_pixel_to_img(&cub3d->raycast_img, x, i, get_trgb(0, 13, 59, 102));
            else
                put_pixel_to_img(&cub3d->raycast_img, x, i, get_trgb(0, 107, 92, 165));
        }
        else
            put_pixel_to_img(&cub3d->raycast_img, x, i, cub3d->colors.floor);
        i++;
    }
}

void    raycast_initialize(t_cub3d *cub3d, t_raycast *raycast, int x)
{
    raycast->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
    raycast->rayDirX = cub3d->player.dirX + raycast->planeX * raycast->cameraX;
    raycast->rayDirY = cub3d->player.dirY + raycast->planeY * raycast->cameraX;
    raycast->mapX = (int)cub3d->player.posX;
    raycast->mapY = (int)cub3d->player.posY;
    raycast->deltaDistX = (raycast->rayDirX == 0) ? 1e30 : fabs(1 / raycast->rayDirX);
    raycast->deltaDistY = (raycast->rayDirY == 0) ? 1e30 : fabs(1 / raycast->rayDirY);
    raycast->hit = 0;
    if (raycast->rayDirX < 0)
    {
      raycast->stepX = -1;
      raycast->sideDistX = (cub3d->player.posX - raycast->mapX) * raycast->deltaDistX;
    }
    else
    {
      raycast->stepX = 1;
      raycast->sideDistX = (raycast->mapX + 1.0 - cub3d->player.posX) * raycast->deltaDistX;
    }
    if (raycast->rayDirY < 0)
    {
      raycast->stepY = -1;
      raycast->sideDistY = (cub3d->player.posY - raycast->mapY) * raycast->deltaDistY;
    }
    else
    {
      raycast->stepY = 1;
      raycast->sideDistY = (raycast->mapY + 1.0 - cub3d->player.posY) * raycast->deltaDistY;
    }
}

void    raycast_find_wall(t_cub3d *cub3d, t_raycast *raycast)
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
        if (cub3d->map[raycast->mapY][raycast->mapX] == '1') 
            raycast->hit = 1;
    }
    if (raycast->side == 0)
        raycast->perpWallDist = (raycast->sideDistX - raycast->deltaDistX);
    else
        raycast->perpWallDist = (raycast->sideDistY - raycast->deltaDistY);
}

void    raycast(t_cub3d *cub3d, t_raycast *raycast)
{
    int x;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        raycast_initialize(cub3d, raycast, x);
        raycast_find_wall(cub3d, raycast);
        raycast->lineHeight = (int)(SCREEN_HEIGHT / raycast->perpWallDist);
        raycast->drawStart = -raycast->lineHeight / 2 + SCREEN_HEIGHT / 2;
        if(raycast->drawStart < 0)
            raycast->drawStart = 0;
        raycast->drawEnd = raycast->lineHeight / 2 + SCREEN_HEIGHT / 2;
        if(raycast->drawEnd >= SCREEN_HEIGHT)
            raycast->drawEnd = SCREEN_HEIGHT - 1;
        draw_line(cub3d, x);
        x++;
    }
	  mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->raycast_img.img, 0, 0);
}