/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 00:01:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/04 18:15:20 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_to_img(t_tex *img, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	*(int *)(img->addr + ((x + y * SCREEN_WIDTH) * img->bpp)) = color;
}

float   get_open_percentage(t_cub3d *cub3d)
{
    int i;

    i = 0;
    while (i < cub3d->doors_nbr)
    {
        if ((int)cub3d->doors[i].x == cub3d->raycast.mapX && (int)cub3d->doors[i].y == cub3d->raycast.mapY)
            return ((float)cub3d->doors[i].step_percent / 100);
        i++;
    }
    return (-1.0f);    
}
static int draw_line(t_cub3d *cub3d, int x)
{
    unsigned char   *pixel;
    int             i;
    int             texY;
    double          step;
    double          texPos;
    int             reached_door_end;
    t_image         sprite;

    reached_door_end = 0;
    sprite = cub3d->sprites[cub3d->raycast.texNum];
    step = 1.0 * cub3d->sprites[cub3d->raycast.texNum].y / cub3d->raycast.lineHeight;
    texPos = (cub3d->raycast.drawStart - SCREEN_HEIGHT / 2 + cub3d->raycast.lineHeight / 2) * step;
    i = 0;
    while (i < SCREEN_HEIGHT)
    {
        if (i < cub3d->raycast.drawStart)
            put_pixel_to_img(&cub3d->raycast_img, x, i, cub3d->colors.sky);
        else if (i < cub3d->raycast.drawEnd)
        {
            texY = (int)texPos & (cub3d->sprites[cub3d->raycast.texNum].y - 1);
            texPos += step;    
            pixel = &sprite.pixels[texY * sprite.line_len + cub3d->raycast.texX * (sprite.bits_per_pixel / 8)];
            if (cub3d->raycast.texNum == 4 && cub3d->raycast.texX * (sprite.bits_per_pixel / 8) < sprite.line_len * get_open_percentage(cub3d))
                reached_door_end = 1;
            else if (cub3d->raycast.texNum == 4)
            {
                pixel = &sprite.pixels[(int)(texY * sprite.line_len + cub3d->raycast.texX * (sprite.bits_per_pixel / 8) + sprite.line_len * (1 - get_open_percentage(cub3d)) - ((int)(sprite.line_len * (1 - get_open_percentage(cub3d))) % (sprite.bits_per_pixel / 8)))];
                put_pixel_to_img(&cub3d->raycast_img, x, i, get_trgb(0, pixel[2], pixel[1], pixel[0]));
            }
            else
                put_pixel_to_img(&cub3d->raycast_img, x, i, get_trgb(0, pixel[2], pixel[1], pixel[0]));
        }
        else
            put_pixel_to_img(&cub3d->raycast_img, x, i, cub3d->colors.floor);
        i++;
    }
    return (reached_door_end);
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

void    raycast_find_wall(t_cub3d *cub3d, t_raycast *raycast, int do_hit_door)
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
            || (do_hit_door == 1 && cub3d->map_struct.map_strs[raycast->mapY][raycast->mapX] == 'D')) 
            raycast->hit = 1;
    }
    if (raycast->side == 0)
        raycast->perpWallDist = (raycast->sideDistX - raycast->deltaDistX);
    else
        raycast->perpWallDist = (raycast->sideDistY - raycast->deltaDistY);
}

void find_texture_index(t_cub3d *cub3d)
{
    if (cub3d->map_struct.map_strs[cub3d->raycast.mapY][cub3d->raycast.mapX] == 'D')
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

void    texture_calculation(t_cub3d *cub3d)
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
    if(cub3d->raycast.side == 0 && cub3d->raycast.rayDirX > 0)
        cub3d->raycast.texX = cub3d->sprites[cub3d->raycast.texNum].x
            - cub3d->raycast.texX - 1;
    if(cub3d->raycast.side == 1 && cub3d->raycast.rayDirY < 0)
        cub3d->raycast.texX = cub3d->sprites[cub3d->raycast.texNum].x
            - cub3d->raycast.texX - 1;
}

void    insert_torch(t_cub3d *cub3d/* , t_raycast *raycast */)
{
    int x;
    int y;
    unsigned char   *pixel;

    y = 0;
    while (y < cub3d->torch_sprites[0].y)
    {
        x = 0;
        while (x < cub3d->torch_sprites[0].x)
        {
            pixel = &cub3d->torch_sprites[0].pixels[y * cub3d->torch_sprites[0].line_len + x * (cub3d->torch_sprites[0].bits_per_pixel / 8)];
            if (pixel[2] != 0 && pixel[1] != 0 && pixel[0] != 0)
                put_pixel_to_img(&cub3d->raycast_img, TORCH_POS_X + x, TORCH_POS_Y + y, get_trgb(0, pixel[2], pixel[1], pixel[0]));
            x++;
        }
        y++;
    }
}

void    insert_flame(t_cub3d *cub3d)
{
    int x;
    int y;
    static int      frame = 1;
    unsigned char   *pixel;

    y = 0;
    pixel = NULL;
    while (y < cub3d->torch_sprites[frame].y)
    {
        x = 0;
        while (x < cub3d->torch_sprites[frame].x)
        {
            pixel = &cub3d->torch_sprites[frame].pixels[y * cub3d->torch_sprites[frame].line_len + x * (cub3d->torch_sprites[frame].bits_per_pixel / 8)];
            if (pixel[2] != 0 && pixel[1] != 0 && pixel[0] != 0)
                put_pixel_to_img(&cub3d->raycast_img, FIRE_POS_X + x, FIRE_POS_Y + y, get_trgb(0, pixel[2], pixel[1], pixel[0]));
            x++;
        }
        y++;
    }
    frame++;
    if (frame > 7)
        frame = 1;
}

void    raycast(t_cub3d *cub3d, t_raycast *raycast)
{
    int x;
    int hit_door;

    x = 0;
    hit_door = 1;
    while (x < SCREEN_WIDTH)
    {
        raycast_initialize(cub3d, raycast, x);
        raycast_find_wall(cub3d, raycast, hit_door);
        raycast->lineHeight = (int)(SCREEN_HEIGHT / raycast->perpWallDist);
        raycast->drawStart = -raycast->lineHeight / 2 + SCREEN_HEIGHT / 2;
        if(raycast->drawStart < 0)
            raycast->drawStart = 0;
        raycast->drawEnd = raycast->lineHeight / 2 + SCREEN_HEIGHT / 2;
        if(raycast->drawEnd >= SCREEN_HEIGHT)
            raycast->drawEnd = SCREEN_HEIGHT - 1;
        texture_calculation(cub3d);
        if (draw_line(cub3d, x))
            hit_door = 0;
        x++;
    }
    insert_torch(cub3d);
    insert_flame(cub3d);
    put_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->raycast_img.img, 0, 0);
}
