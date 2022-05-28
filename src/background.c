/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 02:27:22 by charles           #+#    #+#             */
/*   Updated: 2022/05/28 02:51:06 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_background(t_cub3d *cub3d)
{
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->background_img.img, 0, 0);
}

static void	put_pixel_to_img(t_tex *img, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	*(int *)(img->addr + ((x + y * SCREEN_WIDTH) * img->bpp)) = color;
}

void	draw_background(t_cub3d *cub3d)
{
	int x_pixel;
	int y_pixel;

    y_pixel = 0;
	while (y_pixel < SCREEN_WIDTH)
	{
        x_pixel = 0;
		while (x_pixel < SCREEN_WIDTH)
		{
            if (y_pixel < SCREEN_WIDTH / 2)
                put_pixel_to_img(&cub3d->background_img, x_pixel, y_pixel, cub3d->colors.sky);
            else
		        put_pixel_to_img(&cub3d->background_img, x_pixel, y_pixel, cub3d->colors.floor);
		x_pixel++;
		}
		y_pixel++;
	}
}
