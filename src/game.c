/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:06:45 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/28 02:39:00 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_vision(t_cub3d *cub3d)
{
	if (cub3d->keyboard.right && !cub3d->keyboard.left)
		cub3d->p_angle -= VISION_MOVE_PER_FRAME;
	else if (cub3d->keyboard.left && !cub3d->keyboard.right)
		cub3d->p_angle += VISION_MOVE_PER_FRAME;
	if (cub3d->p_angle > 360)
		cub3d->p_angle -= 360;
	else if (cub3d->p_angle < 0)
		cub3d->p_angle += 360;
}

static void	move_player(t_cub3d *cub3d)
{
	cub3d->p_vector_x = 0;
	cub3d->p_vector_y = 0;
	if (cub3d->keyboard.top && !cub3d->keyboard.bottom)
	{
		cub3d->p_vector_x = MOVE_PER_FRAME * sinf(cub3d->p_angle);
		cub3d->p_vector_y = MOVE_PER_FRAME * cosf(cub3d->p_angle);
	}
	else if (cub3d->keyboard.bottom && !cub3d->keyboard.top)
	{
		cub3d->p_vector_x = -MOVE_PER_FRAME * sinf(cub3d->p_angle);
		cub3d->p_vector_y = -MOVE_PER_FRAME * cosf(cub3d->p_angle);
	}
 	if (cub3d->map[(int)(cub3d->p_pos_y + cub3d->p_vector_y)][(int)(cub3d->p_pos_x + cub3d->p_vector_x)] == '0')
 	{
 		cub3d->p_pos_y += cub3d->p_vector_y;
    	cub3d->p_pos_x += cub3d->p_vector_x;
	}
}

int	key_press_hook(int key, t_cub3d *cub3d)
{
	if (key == D || key == RIGHT)
		cub3d->keyboard.right = 1;
	else if (key == A || key == LEFT)
		cub3d->keyboard.left = 1;
	else if (key == W || key == TOP)
		cub3d->keyboard.top = 1;
	else if (key == S || key == BOTTOM)
		cub3d->keyboard.bottom = 1;
	else if (key == ESC)
		exit_game(cub3d, "Game exited by user.", EXIT_SUCCESS);
	return (0);
}

int	key_release_hook(int key, t_cub3d *cub3d)
{
	if (key == D || key == RIGHT)
		cub3d->keyboard.right = 0;
	else if (key == A || key == LEFT)
		cub3d->keyboard.left = 0;
	else if (key == W || key == TOP)
		cub3d->keyboard.top = 0;
	else if (key == S || key == BOTTOM)
		cub3d->keyboard.bottom = 0;
	return (0);
}

int    loop(t_cub3d *cub3d)
{
	move_vision(cub3d);
	move_player(cub3d);
	put_background(cub3d);
    put_minimap(cub3d);
    put_overlay(cub3d);
    return (0);
}

void   game_loop(t_cub3d *cub3d)
{
	mlx_hook(cub3d->mlx_win, 17, 0L, exit_button, cub3d);
	mlx_hook(cub3d->mlx_win, 02, 1L<<0, key_press_hook, cub3d);
	mlx_hook(cub3d->mlx_win, 03, 1L<<1, key_release_hook, cub3d);
    mlx_loop_hook(cub3d->mlx, loop, (void *)cub3d);
    mlx_loop(cub3d->mlx);
}
