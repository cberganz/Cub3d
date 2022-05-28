/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 02:06:38 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/28 02:54:27 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	overlay_display(t_cub3d *cub3d)
{
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->overlay_img.img, 0, SCREEN_WIDTH);
}

static void	put_pixel_to_img(t_tex *img, int x, int y, int color)
{
	if (x < 0 || x >= OVERLAY_WIDTH || y < 0 || y >= OVERLAY_HEIGHT)
		return ;
	*(int *)(img->addr + ((x + y * OVERLAY_WIDTH) * img->bpp)) = color;
}

static void	draw_overlay(t_cub3d *cub3d)
{
	int x_pixel;
	int y_pixel;

    y_pixel = 0;
	while (y_pixel < OVERLAY_HEIGHT)
	{
        x_pixel = 0;
		while (x_pixel < OVERLAY_WIDTH)
		{
		    put_pixel_to_img(&cub3d->overlay_img, x_pixel, y_pixel, OVERLAY_BACKGROUND_COLOR);
			x_pixel++;
		}
		y_pixel++;
	}
}

void    put_overlay(t_cub3d *cub3d)
{
    draw_overlay(cub3d);
    overlay_display(cub3d);
}