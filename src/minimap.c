/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:15:12 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/28 02:58:02 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_display(t_cub3d *cub3d)
{
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->minimap_img.img, 0, 0);
}

static void	put_pixel_to_img(t_tex *img, int x, int y, int color)
{
	if (x < 0 || x >= MINIMAP_WIDTH || y < 0 || y >= MINIMAP_HEIGHT)
		return ;
	*(int *)(img->addr + ((x + y * MINIMAP_WIDTH) * img->bpp)) = color;
}

static int    get_color(t_cub3d *cub3d, int x, int y)
{
    if (x < 0 || x >= cub3d->width || y < 0 || y >= cub3d->height)
        return (MINIMAP_OUTMAP_COLOR);
    if (cub3d->map[y][x] == '1')
        return (MINIMAP_WALL_COLOR);
    else if (cub3d->map[y][x] == '0')
        return (MINIMAP_FLOOR_COLOR);
    else
        return (MINIMAP_OUTMAP_COLOR);
}

static uint8_t is_on_vector_line(t_cub3d *cub3d, float x, float y)
{
    float x_projection;
    float y_projection;

	x_projection = MINIMAP_CENTER + DIRECTION_LINE_SIZE * sinf(cub3d->p_angle);
	y_projection = MINIMAP_CENTER + DIRECTION_LINE_SIZE * cosf(cub3d->p_angle);
    return (get_distance(MINIMAP_CENTER, MINIMAP_CENTER, x, y) + get_distance(x_projection, y_projection, x, y) > get_distance(MINIMAP_CENTER, MINIMAP_CENTER, x_projection, y_projection) - DIRECTION_LINE_WIDTH
            && get_distance(MINIMAP_CENTER, MINIMAP_CENTER, x, y) + get_distance(x_projection, y_projection, x, y) < get_distance(MINIMAP_CENTER, MINIMAP_CENTER, x_projection, y_projection) + DIRECTION_LINE_WIDTH);
}

static uint8_t is_on_center_square(int x, int y)
{
    int square_begin_x;
    int square_begin_y;
    int square_size;

    square_begin_x = (MINIMAP_WIDTH / 2) - (PIXEL_PER_CUBE / 2);
    square_begin_y = (MINIMAP_HEIGHT / 2) - (PIXEL_PER_CUBE / 2);
    square_size = PIXEL_PER_CUBE;
    return (x >= square_begin_x && x < square_begin_x + square_size && y >= square_begin_y && y < square_begin_y + square_size);
}

static void	draw_minimap(t_cub3d *cub3d)
{
	int x_pixel;
	int y_pixel;
	float x_map;
	float y_map;

    y_pixel = 0;
	y_map = cub3d->p_pos_y - SIZE_AROUND_PLAYER;
	while (y_pixel < MINIMAP_HEIGHT)
	{
        x_pixel = 0;
	    x_map = cub3d->p_pos_x - SIZE_AROUND_PLAYER;
		while (x_pixel < MINIMAP_WIDTH)
		{
            if (is_on_vector_line(cub3d, x_pixel, y_pixel) || is_on_center_square(x_pixel, y_pixel))
		        put_pixel_to_img(&cub3d->minimap_img, x_pixel, y_pixel, MINIMAP_PLAYER_COLOR);
            else
		        put_pixel_to_img(&cub3d->minimap_img, x_pixel, y_pixel, get_color(cub3d, x_map, y_map));
            x_map += 1.0f / PIXEL_PER_CUBE;
			x_pixel++;
		}
        y_map += 1.0f / PIXEL_PER_CUBE;
		y_pixel++;
	}
}

void    put_minimap(t_cub3d *cub3d)
{
    draw_minimap(cub3d);
    minimap_display(cub3d);
}
