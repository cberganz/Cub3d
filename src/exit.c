/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:56:55 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/30 18:46:17 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     exit_button(t_cub3d *cub3d)
{
    exit_game(cub3d, "Game exited by user.", EXIT_SUCCESS);
    return (0);
}

void    exit_game(t_cub3d *cub3d, char *msg, int exit_status)
{
    int i;

    i = 0;
    mlx_destroy_window(cub3d->mlx, cub3d->mlx_win);
    mlx_destroy_image(cub3d->mlx, cub3d->minimap_img.img);
    mlx_destroy_image(cub3d->mlx, cub3d->overlay_img.img);
    mlx_destroy_image(cub3d->mlx, cub3d->raycast_img.img);
    while (i < 4)//peut etre check que les images existent avant de les destroy
    {
        mlx_destroy_image(cub3d->mlx, cub3d->sprites[i].reference);
        i++;
    }
    mlx_destroy_display(cub3d->mlx);
    del_garbage(0);
    if (exit_status == 0)
        ft_putendl_fd(msg, 1);
    else
        ft_putendl_fd(msg, 2);
    exit(exit_status);
}
