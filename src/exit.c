/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:56:55 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 20:20:54 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_button(t_cub3d *cub3d)
{
	exit_game(cub3d, "Game exited by user.", EXIT_SUCCESS);
	return (0);
}

void	exit_game(t_cub3d *cub3d, char *msg, int exit_status)
{
	int	i;

	mlx_destroy_window(cub3d->mlx, cub3d->mlx_win);
	mlx_destroy_image(cub3d->mlx, cub3d->minimap_img.img);
	mlx_destroy_image(cub3d->mlx, cub3d->raycast_img.img);
	i = -1;
	while (++i < 4)//peut etre check que les images existent avant de les destroy
		mlx_destroy_image(cub3d->mlx, cub3d->sprites[i].reference);
	if (BONUS_FLAG && cub3d->doors_nbr)
		mlx_destroy_image(cub3d->mlx, cub3d->sprites[4].reference);
	i = -1;
	while (++i < 8)//peut etre check que les images existent avant de les destroy
		mlx_destroy_image(cub3d->mlx, cub3d->torch_sprites[i].reference);
	mlx_destroy_display(cub3d->mlx);
	del_garbage(0);
	if (exit_status == 0)
		ft_putendl_fd(msg, 1);
	else
		ft_putendl_fd(msg, 2);
	exit(exit_status);
}
