/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:06:45 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/29 17:04:04 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_vision(t_cub3d *cub3d)
{
	double	oldDirX;
 	double	oldPlaneX;
	int		x;
	int		y;
	int		speed;

	oldDirX = cub3d->player.dirX;
 	oldPlaneX = cub3d->raycast.planeX;
    mlx_mouse_get_pos(cub3d->mlx, cub3d->mlx_win, &x, &y);
	speed = abs(x - SCREEN_WIDTH / 2) > 0 ? abs(x - SCREEN_WIDTH / 2) / 2 : 1;
	if ((x > SCREEN_WIDTH / 2 && cub3d->mouse_set) || (cub3d->keyboard.right && !cub3d->keyboard.left))
	{
 		cub3d->player.dirX = cub3d->player.dirX * cos(CAMERA_SPEED * speed) - cub3d->player.dirY * sin(CAMERA_SPEED * speed);
 		cub3d->player.dirY = oldDirX * sin(CAMERA_SPEED * speed) + cub3d->player.dirY * cos(CAMERA_SPEED * speed);
 		cub3d->raycast.planeX = cub3d->raycast.planeX * cos(CAMERA_SPEED * speed) - cub3d->raycast.planeY * sin(CAMERA_SPEED * speed);
		cub3d->raycast.planeY = oldPlaneX * sin(CAMERA_SPEED * speed) + cub3d->raycast.planeY * cos(CAMERA_SPEED * speed);
	}
	else if ((x < SCREEN_WIDTH / 2 && cub3d->mouse_set) || (cub3d->keyboard.left && !cub3d->keyboard.right))
	{
 		cub3d->player.dirX = cub3d->player.dirX * cos(-CAMERA_SPEED * speed) - cub3d->player.dirY * sin(-CAMERA_SPEED * speed);
 		cub3d->player.dirY = oldDirX * sin(-CAMERA_SPEED * speed) + cub3d->player.dirY * cos(-CAMERA_SPEED * speed);
 		cub3d->raycast.planeX = cub3d->raycast.planeX * cos(-CAMERA_SPEED * speed) - cub3d->raycast.planeY * sin(-CAMERA_SPEED * speed);
		cub3d->raycast.planeY = oldPlaneX * sin(-CAMERA_SPEED * speed) + cub3d->raycast.planeY * cos(-CAMERA_SPEED * speed);
	}
}

static void	move_player(t_cub3d *cub3d)
{
	if (cub3d->keyboard.top && !cub3d->keyboard.bottom)
	{
 		if (cub3d->map[(int)(cub3d->player.posY + cub3d->player.dirY * MOVE_SPEED)][(int)cub3d->player.posX] == '0')
 			cub3d->player.posY += cub3d->player.dirY * MOVE_SPEED;
 		if (cub3d->map[(int)cub3d->player.posY][(int)(cub3d->player.posX + cub3d->player.dirX * MOVE_SPEED)] == '0')
  		  	cub3d->player.posX += cub3d->player.dirX * MOVE_SPEED;
	}
	else if (cub3d->keyboard.bottom && !cub3d->keyboard.top)
	{
 		if (cub3d->map[(int)(cub3d->player.posY - cub3d->player.dirY * MOVE_SPEED)][(int)cub3d->player.posX] == '0')
 			cub3d->player.posY -= cub3d->player.dirY * MOVE_SPEED;
 		if (cub3d->map[(int)cub3d->player.posY][(int)(cub3d->player.posX - cub3d->player.dirX * MOVE_SPEED)] == '0')
  		  	cub3d->player.posX -= cub3d->player.dirX * MOVE_SPEED;
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
	else if (key == CTRL)
		set_mouse(cub3d);
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
	if (cub3d->mouse_set)
 		mlx_mouse_move(cub3d->mlx, cub3d->mlx_win, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);
	move_player(cub3d);
	raycast(cub3d, &cub3d->raycast);
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
