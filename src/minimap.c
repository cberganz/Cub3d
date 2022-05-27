/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:15:12 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/27 03:40:12 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minimap.h"
#include <stdio.h>

int	get_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	minimap_display(t_minimap *minimap)
{
	mlx_put_image_to_window(minimap->mlx, minimap->mlx_win, minimap->map_img.img, 0, 0);
}

void    *minimap_initialize(t_minimap *minimap, t_tex *map_img)
{
    map_img->img = mlx_new_image(minimap->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
    if (map_img->img == NULL)
        return (NULL);
    map_img->addr = mlx_get_data_addr(map_img->img, &map_img->bpp, &map_img->line_length, &map_img->endian);
    map_img->bpp /= 8;
    return ((void *)1);
}

void	put_pixel_to_img(t_tex *map_img, int x, int y, int color)
{
	if (x < 0 || x >= MINIMAP_WIDTH || y < 0 || y >= MINIMAP_HEIGHT)
		return ;
	*(int *)(map_img->addr + ((x + y * MINIMAP_WIDTH) * map_img->bpp)) = color;
}

int    get_color(t_minimap *minimap, int x, int y)
{
    if (x < 0 || x >= minimap->width || y < 0 || y >= minimap->height)
        return (get_trgb(0, 41, 32, 73));
    if (minimap->map[y][x] == '1')
        return (0xFF0000);
    else if (minimap->map[y][x] == '0')
        return (0x00FF00);
    if (minimap->map[y][x] == 'N')
        return (0x0000FF);
    else
        return (0x000000);
}

void	draw_img(t_minimap *minimap)
{
	int x_pixel;
	int y_pixel;
	int x_map;
	int y_map;

    y_pixel = 0;
	y_map = minimap->p_pos_y - SIZE_AROUND_PLAYER;
	while (y_pixel < MINIMAP_HEIGHT)
	{
        x_pixel = 0;
	    x_map = minimap->p_pos_x - SIZE_AROUND_PLAYER;
		while (x_pixel < MINIMAP_WIDTH)
		{
		    put_pixel_to_img(&minimap->map_img, x_pixel, y_pixel, get_color(minimap, x_map, y_map));
			x_pixel++;
            if (x_pixel % PIXEL_PER_CUBE == 0)
                x_map++;
		}
		y_pixel++;
        if (y_pixel % PIXEL_PER_CUBE == 0)
            y_map++;
	}
}

int get_player_pos(char **map, int *x, int *y)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N')
            {
                *x = j;
                *y = i;
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int main(void)
{
    t_minimap   minimap;

    minimap.mlx = mlx_init();
    minimap.width = 36;
    minimap.height = 36;
    minimap.map = malloc((minimap.height + 1) * sizeof(char *));
    if (!minimap.map)
        return (-1);
    minimap.map[0] = "111111111111111111111111111111111111\0";
    minimap.map[1] = "100000000000000000000000000000000001\0";
    minimap.map[2] = "100000000000000000000000000000000001\0";
    minimap.map[3] = "100000000000000000000000000000000001\0";
    minimap.map[4] = "100000000000000000000000000000000001\0";
    minimap.map[5] = "100000000000000000000000000000000001\0";
    minimap.map[6] = "100000000000000000000000000000000001\0";
    minimap.map[7] = "100000000000000000000000000000000001\0";
    minimap.map[8] = "100000000000000000000000000000000001\0";
    minimap.map[9] = "100000000000000000000000000000000001\0";
    minimap.map[10] = "100000000000000000000000000000000001\0";
    minimap.map[11] = "100000000000000000000000000000000001\0";
    minimap.map[12] = "100000000000000000000000000000000001\0";
    minimap.map[13] = "100000000000000000000000000000000001\0";
    minimap.map[14] = "100000000000000000000000000000000001\0";
    minimap.map[15] = "100000000000000000000000000000000001\0";
    minimap.map[16] = "100000000000000000000000000000000001\0";
    minimap.map[17] = "100000000000000000000000000000000001\0";
    minimap.map[18] = "100000000000000000000000000000000001\0";
    minimap.map[19] = "100000000000000000000000000000000001\0";
    minimap.map[20] = "100000000000000000000000000000000001\0";
    minimap.map[21] = "100000000000000000000000000000000001\0";
    minimap.map[22] = "100000000000000000000000000000000001\0";
    minimap.map[23] = "100000000000000000000000000000000001\0";
    minimap.map[24] = "100000000000000000000000000000000001\0";
    minimap.map[25] = "100000000000000000000000000000000001\0";
    minimap.map[26] = "100000000000000000000000000000000001\0";
    minimap.map[27] = "100000000000000000000000000000000001\0";
    minimap.map[28] = "100000000000000000000000000000000001\0";
    minimap.map[29] = "100000000000000000000000000000000001\0";
    minimap.map[30] = "100000000000000000000000000000000001\0";
    minimap.map[31] = "100000000000000000000000000000000001\0";
    minimap.map[32] = "100000000000000000000000000001100001\0";
    minimap.map[33] = "10000000000000000000000000000100N001\0";
    minimap.map[34] = "100000000000000000000000000001000001\0";
    minimap.map[35] = "111111111111111111111111111111111111\0";
    minimap.map[36] = NULL;
    get_player_pos(minimap.map, &minimap.p_pos_x, &minimap.p_pos_y);
    if (!minimap_initialize(&minimap, &minimap.map_img))
        return (-1);
    draw_img(&minimap);
    minimap.mlx_win = mlx_new_window(minimap.mlx, WIDTH, HEIGHT, "Cub3d");
    minimap_display(&minimap);
    mlx_loop(minimap.mlx);

    return (0);
}