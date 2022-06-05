/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:06:45 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 19:23:22 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_cam(t_cub3d *cub3d, t_player *player, int sign, float speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dirX;
	old_planex = cub3d->raycast.planeX;
	player->dirX = player->dirX * cos(cub3d->camera_speed * speed * sign)
		- player->dirY * sin(cub3d->camera_speed * speed * sign);
	player->dirY = old_dirx * sin(cub3d->camera_speed * speed * sign)
		+ player->dirY * cos(cub3d->camera_speed * speed * sign);
	cub3d->raycast.planeX = cub3d->raycast.planeX
		* cos(cub3d->camera_speed * speed * sign) - cub3d->raycast.planeY
		* sin(cub3d->camera_speed * speed * sign);
	cub3d->raycast.planeY = old_planex * sin(cub3d->camera_speed * speed * sign)
		+ cub3d->raycast.planeY * cos(cub3d->camera_speed * speed * sign);
}

static void	move_vision(t_cub3d *cub3d, t_player *player)
{
	int		x;
	int		y;
	float	speed;

	mlx_mouse_get_pos(cub3d->mlx, cub3d->mlx_win, &x, &y);
	if (ft_absf(x - SCREEN_WIDTH / 2) > 0 && cub3d->mouse_set)
		speed = ft_absf(x - SCREEN_WIDTH / 2) / 2;
	else
		speed = 1;
	if ((x > SCREEN_WIDTH / 2 && cub3d->mouse_set)
		|| (cub3d->keyboard.right_rotate && !cub3d->keyboard.left_rotate))
		update_cam(cub3d, player, 1, speed);
	else if ((x < SCREEN_WIDTH / 2 && cub3d->mouse_set)
		|| (cub3d->keyboard.left_rotate && !cub3d->keyboard.right_rotate))
		update_cam(cub3d, player, -1, speed);
}

static uint8_t	hitbox_wallhit(t_cub3d *cub3d, double x, double y)
{	
	return (cub3d->map_struct.map_strs[(int)y][(int)(x + HITBOX_SIZE)] == '0'
		&& cub3d->map_struct.map_strs[(int)y][(int)(x - HITBOX_SIZE)] == '0'
		&& cub3d->map_struct.map_strs[(int)(y + HITBOX_SIZE)][(int)x] == '0'
		&& cub3d->map_struct.map_strs[(int)(y - HITBOX_SIZE)][(int)x] == '0');
}

static void	move_forward_back(t_cub3d *cub3d, t_player *player, int sign)
{
	if (hitbox_wallhit(cub3d, player->posX, player->posY
			+ (player->dirY * cub3d->move_speed * sign)))
		player->posY += player->dirY * cub3d->move_speed * sign;
	if (hitbox_wallhit(cub3d, player->posX
			+ (player->dirX * cub3d->move_speed * sign), player->posY))
		player->posX += player->dirX * cub3d->move_speed * sign;
}

static void	move_right_left(t_cub3d *cub3d, t_player *player, int sign)
{
	double	old_dirx;

	old_dirx = player->dirX;
	if (hitbox_wallhit(cub3d, player->posX
			+ ((player->dirX * cos(ROTATION_ANGLE * sign) - player->dirY
					* sin(ROTATION_ANGLE * sign)) * cub3d->move_speed),
			player->posY))
		player->posX += (player->dirX * cos(ROTATION_ANGLE * sign)
				- player->dirY * sin(ROTATION_ANGLE * sign))
			* cub3d->move_speed;
	if (hitbox_wallhit(cub3d, player->posX, player->posY + (old_dirx
				* sin(ROTATION_ANGLE * sign) + player->dirY
				* cos(ROTATION_ANGLE * sign)) * cub3d->move_speed))
		player->posY += (old_dirx * sin(ROTATION_ANGLE * sign) + player->dirY
				* cos(ROTATION_ANGLE * sign)) * cub3d->move_speed;
}

static void	move_player(t_cub3d *cub3d, t_player *player)
{
	if (cub3d->keyboard.top && !cub3d->keyboard.bottom)
		move_forward_back(cub3d, player, 1);
	else if (cub3d->keyboard.bottom && !cub3d->keyboard.top)
		move_forward_back(cub3d, player, -1);
	if (cub3d->keyboard.right && !cub3d->keyboard.left)
		move_right_left(cub3d, player, 1);
	else if (cub3d->keyboard.left && !cub3d->keyboard.right)
		move_right_left(cub3d, player, -1);
}

void	speed_key(t_cub3d *cub3d, int key)
{
	if (key == PLUS)
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
	else if (key == CTRL && BONUS_FLAG)
		set_mouse(cub3d);
	else if (key == ESC)
		exit_game(cub3d, "Game exited by user.", EXIT_SUCCESS);
	else if (key == PLUS || key == MINUS)
		speed_key(cub3d, key);
	return (0);
}

t_door	*targeted_door(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->doors_nbr)
	{
		if (cub3d->player.dirX + cub3d->player.posX > cub3d->doors[i].x
			&& cub3d->player.dirX + cub3d->player.posX < cub3d->doors[i].x + 1
			&& cub3d->player.dirY + cub3d->player.posY > cub3d->doors[i].y
			&& cub3d->player.dirY + cub3d->player.posY < cub3d->doors[i].y + 1)
			return (&cub3d->doors[i]);
		i++;
	}
	return (NULL);
}

static uint8_t	is_on_door(t_cub3d *cub3d, t_door *targeted_door)
{
	return (((int)targeted_door->x == (int)(cub3d->player.posX + HITBOX_SIZE)
		&& (int)targeted_door->y == (int)cub3d->player.posY)
		|| ((int)targeted_door->x == (int)(cub3d->player.posX - HITBOX_SIZE)
		&& (int)targeted_door->y == (int)cub3d->player.posY)
		|| ((int)targeted_door->x == (int)cub3d->player.posX
		&& (int)targeted_door->y == (int)(cub3d->player.posY + HITBOX_SIZE))
		|| ((int)targeted_door->x == (int)cub3d->player.posX
		&& (int)targeted_door->y == (int)(cub3d->player.posY - HITBOX_SIZE)));
}

void	space_key(t_cub3d *cub3d)
{
	t_door	*door;

	door = targeted_door(cub3d);
	if (door)
	{
		if (door->step_percent == 0 && !is_on_door(cub3d, door))
		{
			door->step_percent = 1;
			door->increment_step = 1;
		}
		else if (door->step_percent == 100 && !is_on_door(cub3d, door))
		{
			door->step_percent = 99;
			door->increment_step = -1;
			cub3d->map_struct.map_strs[door->y][door->x] = 'D';
		}
	}
}

int	key_release_hook(int key, t_cub3d *cub3d)
{
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
		space_key(cub3d);
	return (0);
}

void	update_door_loop(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->doors_nbr)
	{
		if (cub3d->doors[i].step_percent > 0
			&& cub3d->doors[i].step_percent < 100)
			cub3d->doors[i].step_percent += cub3d->doors[i].increment_step;
		else if (cub3d->doors[i].step_percent == 100
			&& cub3d->map_struct.map_strs[cub3d->doors[i].y][cub3d->doors[i].x]
				== 'D')
			cub3d->map_struct.map_strs[cub3d->doors[i].y][cub3d->doors[i].x]
				= '0';
		i++;
	}
}

int	loop(t_cub3d *cub3d)
{
	move_vision(cub3d, &cub3d->player);
	if (BONUS_FLAG && cub3d->mouse_set)
		mlx_mouse_move(cub3d->mlx, cub3d->mlx_win,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	move_player(cub3d, &cub3d->player);
	update_door_loop(cub3d);
	raycast(cub3d, &cub3d->raycast);
	return (0);
}

void	game_loop(t_cub3d *cub3d)
{
	mlx_hook(cub3d->mlx_win, 17, 0L, exit_button, cub3d);
	mlx_hook(cub3d->mlx_win, 02, 1L << 0, key_press_hook, cub3d);
	mlx_hook(cub3d->mlx_win, 03, 1L << 1, key_release_hook, cub3d);
	mlx_loop_hook(cub3d->mlx, loop, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
