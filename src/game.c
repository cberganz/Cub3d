/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:06:45 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 16:23:04 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define PLAYER cub3d->player
static void	move_vision(t_cub3d *cub3d)
{
	double	oldDirX;
 	double	oldPlaneX;
	int		x;
	int		y;
	float	speed;

	oldDirX = PLAYER.dirX;
 	oldPlaneX = cub3d->raycast.planeX;
    mlx_mouse_get_pos(cub3d->mlx, cub3d->mlx_win, &x, &y);
	speed = abs(x - SCREEN_WIDTH / 2) > 0 && cub3d->mouse_set ? abs(x - SCREEN_WIDTH / 2) / 2 : 1;
	if ((x > SCREEN_WIDTH / 2 && cub3d->mouse_set) || (cub3d->keyboard.right_rotate && !cub3d->keyboard.left_rotate))
	{
 		PLAYER.dirX = PLAYER.dirX * cos(cub3d->camera_speed * speed) - PLAYER.dirY * sin(cub3d->camera_speed * speed);
 		PLAYER.dirY = oldDirX * sin(cub3d->camera_speed * speed) + PLAYER.dirY * cos(cub3d->camera_speed * speed);
 		cub3d->raycast.planeX = cub3d->raycast.planeX * cos(cub3d->camera_speed * speed) - cub3d->raycast.planeY * sin(cub3d->camera_speed * speed);
		cub3d->raycast.planeY = oldPlaneX * sin(cub3d->camera_speed * speed) + cub3d->raycast.planeY * cos(cub3d->camera_speed * speed);
	}
	else if ((x < SCREEN_WIDTH / 2 && cub3d->mouse_set) || (cub3d->keyboard.left_rotate && !cub3d->keyboard.right_rotate))
	{
 		PLAYER.dirX = PLAYER.dirX * cos(-cub3d->camera_speed * speed) - PLAYER.dirY * sin(-cub3d->camera_speed * speed);
 		PLAYER.dirY = oldDirX * sin(-cub3d->camera_speed * speed) + PLAYER.dirY * cos(-cub3d->camera_speed * speed);
 		cub3d->raycast.planeX = cub3d->raycast.planeX * cos(-cub3d->camera_speed * speed) - cub3d->raycast.planeY * sin(-cub3d->camera_speed * speed);
		cub3d->raycast.planeY = oldPlaneX * sin(-cub3d->camera_speed * speed) + cub3d->raycast.planeY * cos(-cub3d->camera_speed * speed);
	}
}

static uint8_t	hitbox_wallhit(t_cub3d *cub3d, double x, double y)
{	
	return (cub3d->map_struct.map_strs[(int)y][(int)(x + HITBOX_SIZE)] == '0'
			&& cub3d->map_struct.map_strs[(int)y][(int)(x - HITBOX_SIZE)] == '0'
			&& cub3d->map_struct.map_strs[(int)(y + HITBOX_SIZE)][(int)x] == '0'
			&& cub3d->map_struct.map_strs[(int)(y - HITBOX_SIZE)][(int)x] == '0');
}

static void	move_player(t_cub3d *cub3d)
{
	double	oldDirX;

	oldDirX = PLAYER.dirX;
	if (cub3d->keyboard.top && !cub3d->keyboard.bottom)
	{
 		if (hitbox_wallhit(cub3d, PLAYER.posX, PLAYER.posY + PLAYER.dirY * cub3d->move_speed))
 			PLAYER.posY += PLAYER.dirY * cub3d->move_speed;
 		if (hitbox_wallhit(cub3d, PLAYER.posX + PLAYER.dirX * cub3d->move_speed, PLAYER.posY))
  		  	PLAYER.posX += PLAYER.dirX * cub3d->move_speed;
	}
	else if (cub3d->keyboard.bottom && !cub3d->keyboard.top)
	{
 		if (hitbox_wallhit(cub3d, PLAYER.posX, PLAYER.posY - PLAYER.dirY * cub3d->move_speed))
 			PLAYER.posY -= PLAYER.dirY * cub3d->move_speed;
 		if (hitbox_wallhit(cub3d, PLAYER.posX - PLAYER.dirX * cub3d->move_speed, PLAYER.posY))
  		  	PLAYER.posX -= PLAYER.dirX * cub3d->move_speed;
	}
	if (cub3d->keyboard.right && !cub3d->keyboard.left)
	{
		if (hitbox_wallhit(cub3d, PLAYER.posX + ((PLAYER.dirX * cos(ROTATION_ANGLE) - PLAYER.dirY * sin(ROTATION_ANGLE)) * cub3d->move_speed), PLAYER.posY))
			PLAYER.posX += (PLAYER.dirX * cos(ROTATION_ANGLE) - PLAYER.dirY * sin(ROTATION_ANGLE)) * cub3d->move_speed;
		if (hitbox_wallhit(cub3d, PLAYER.posX, PLAYER.posY + (oldDirX * sin(ROTATION_ANGLE) + PLAYER.dirY * cos(ROTATION_ANGLE)) * cub3d->move_speed))
 			PLAYER.posY += (oldDirX * sin(ROTATION_ANGLE) + PLAYER.dirY * cos(ROTATION_ANGLE)) * cub3d->move_speed;
	}
	else if (cub3d->keyboard.left && !cub3d->keyboard.right)
	{
		if (hitbox_wallhit(cub3d, PLAYER.posX + ((PLAYER.dirX * cos(-ROTATION_ANGLE) - PLAYER.dirY * sin(-ROTATION_ANGLE)) * cub3d->move_speed), PLAYER.posY))
			PLAYER.posX += (PLAYER.dirX * cos(-ROTATION_ANGLE) - PLAYER.dirY * sin(-ROTATION_ANGLE)) * cub3d->move_speed;
		if (hitbox_wallhit(cub3d, PLAYER.posX, PLAYER.posY + (oldDirX * sin(-ROTATION_ANGLE) + PLAYER.dirY * cos(-ROTATION_ANGLE)) * cub3d->move_speed))
 			PLAYER.posY += (oldDirX * sin(-ROTATION_ANGLE) + PLAYER.dirY * cos(-ROTATION_ANGLE)) * cub3d->move_speed;
	}
}

int	key_press_hook(int key, t_cub3d *cub3d)
{
	if (key == D)
		cub3d->keyboard.right = 1;
	else if (key == A)
		cub3d->keyboard.left = 1;
	else if (key == W || key == TOP)
		cub3d->keyboard.top = 1;
	else if (key == S || key == BOTTOM)
		cub3d->keyboard.bottom = 1;
	else if (key == RIGHT)
		cub3d->keyboard.right_rotate = 1;
	else if (key == LEFT)
		cub3d->keyboard.left_rotate = 1;
	else if (key == CTRL)
		set_mouse(cub3d);
	else if (key == ESC)
		exit_game(cub3d, "Game exited by user.", EXIT_SUCCESS);
	return (0);
}

t_door    *targeted_door(t_cub3d *cub3d)
{
    int i;

    i = 0;
    while (i < cub3d->doors_nbr)
    {
        if (PLAYER.dirX + PLAYER.posX > cub3d->doors[i].x && PLAYER.dirX + PLAYER.posX < cub3d->doors[i].x + 1
			&& PLAYER.dirY + PLAYER.posY > cub3d->doors[i].y && PLAYER.dirY + PLAYER.posY < cub3d->doors[i].y + 1)
            return (&cub3d->doors[i]);
        i++;
    }
	return (NULL);
}

static uint8_t	is_player_on_door(t_cub3d *cub3d, t_door *targeted_door)
{
	return (((int)targeted_door->x == (int)(cub3d->player.posX + HITBOX_SIZE) && (int)targeted_door->y == (int)cub3d->player.posY)
			|| ((int)targeted_door->x == (int)(cub3d->player.posX - HITBOX_SIZE) && (int)targeted_door->y == (int)cub3d->player.posY)
			|| ((int)targeted_door->x == (int)cub3d->player.posX && (int)targeted_door->y == (int)(cub3d->player.posY + HITBOX_SIZE))
			|| ((int)targeted_door->x == (int)cub3d->player.posX && (int)targeted_door->y == (int)(cub3d->player.posY - HITBOX_SIZE)));
}

int	key_release_hook(int key, t_cub3d *cub3d)
{
	t_door	*door;
	if (key == D)
		cub3d->keyboard.right = 0;
	else if (key == A)
		cub3d->keyboard.left = 0;
	else if (key == W || key == TOP)
		cub3d->keyboard.top = 0;
	else if (key == S || key == BOTTOM)
		cub3d->keyboard.bottom = 0;
	else if (key == RIGHT)
		cub3d->keyboard.right_rotate = 0;
	else if (key == LEFT)
		cub3d->keyboard.left_rotate = 0;
	else if (key == SPACE)
	{
		door = targeted_door(cub3d);
		if (door)
		{
			if (door->step_percent == 0 && !is_player_on_door(cub3d, door))
			{
				door->step_percent = 1;
				door->increment_step = 1;
			}
			else if (door->step_percent == 100 && !is_player_on_door(cub3d, door))
			{
				door->step_percent = 99;
				door->increment_step = -1;
				cub3d->map_struct.map_strs[door->y][door->x] = 'D';
			}
		}
	}
	else if (key == PLUS)
	{
		if (cub3d->move_speed + 0.02f < 0.5f)
			cub3d->move_speed += 0.02f;
		if (cub3d->move_speed + 0.01f < 0.2f)
			cub3d->camera_speed += 0.01f;
	}
	else if (key == MINUS)
	{
		if (cub3d->move_speed - 0.02f > 0.01f)
			cub3d->move_speed -= 0.02f;
		if (cub3d->camera_speed - 0.01f > 0.01f)
			cub3d->camera_speed -= 0.01f;
	}
	return (0);
}

void    update_door_loop(t_cub3d *cub3d)
{
    int i;

    i = 0;
    while (i < cub3d->doors_nbr)
    {
        if (cub3d->doors[i].step_percent > 0
            && cub3d->doors[i].step_percent < 100)
            cub3d->doors[i].step_percent += cub3d->doors[i].increment_step;
		else if (cub3d->doors[i].step_percent == 100
			&& cub3d->map_struct.map_strs[cub3d->doors[i].y][cub3d->doors[i].x] == 'D')
			cub3d->map_struct.map_strs[cub3d->doors[i].y][cub3d->doors[i].x] = '0';
        i++;
    }
}

int    loop(t_cub3d *cub3d)
{
	move_vision(cub3d);
	if (cub3d->mouse_set)
 		mlx_mouse_move(cub3d->mlx, cub3d->mlx_win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	move_player(cub3d);
	update_door_loop(cub3d);
	raycast(cub3d, &cub3d->raycast);
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
