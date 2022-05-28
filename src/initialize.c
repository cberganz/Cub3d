/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:56:57 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/28 02:12:48 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    img_initialize(t_cub3d *cub3d, t_tex *img, int width, int height)
{
    img->img = mlx_new_image(cub3d->mlx, width, height);
    if (img->img == NULL)
        exit_game(cub3d, "Error: failed to initialize image.", EXIT_FAILURE);
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
    img->bpp /= 8;
}

void    window_initialize(t_cub3d *cub3d)
{
    cub3d->mlx = mlx_init();
    garbage_addptr(cub3d->mlx, 0);
    cub3d->mlx_win = mlx_new_window(cub3d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
}

void    game_initialize(t_cub3d *cub3d)
{
    cub3d->keyboard.right = 0;
    cub3d->keyboard.left = 0;
    cub3d->keyboard.top = 0;
    cub3d->keyboard.bottom = 0;
}
