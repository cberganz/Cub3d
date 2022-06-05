/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:56:57 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 16:39:23 by cberganz         ###   ########.fr       */
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

void    init_player_direction(t_cub3d *cub3d)
{
    double oldDirX;
    double oldPlanX;
    double angle;

    if (cub3d->player.start_dir == 'N')
        return ;
    else if (cub3d->player.start_dir == 'W')
        angle = (M_PI / 2) * -1;
    else if (cub3d->player.start_dir == 'E')
        angle = M_PI / 2;
    else
        angle = M_PI;
    oldDirX = cub3d->player.dirX;
    oldPlanX = cub3d->raycast.planeX;
    cub3d->player.dirX = cub3d->player.dirX * cos(angle) - cub3d->player.dirY * sin(angle);
    cub3d->player.dirY = oldDirX * sin(angle) + cub3d->player.dirY * cos(angle);
    cub3d->raycast.planeX = cub3d->raycast.planeX * cos(angle) - cub3d->raycast.planeY * sin(angle);
    cub3d->raycast.planeY = oldPlanX * sin(angle) + cub3d->raycast.planeY * cos(angle);
}

void    init_animation_sprites(t_cub3d *cub3d)
{
    int            i;
    char    *sprite_paths[8] = {"sprites/torch/hand_torch.xpm", "sprites/torch/fire1.xpm", "sprites/torch/fire2.xpm", "sprites/torch/fire3.xpm", "sprites/torch/fire4.xpm", "sprites/torch/fire5.xpm", "sprites/torch/fire6.xpm", "sprites/torch/fire7.xpm"};

    i = 0;
    while (i < 8)
    {
        if (!file_exist(sprite_paths[i]) || !is_valid_extension_path(sprite_paths[i], "xpm"))
            exit_game(cub3d, FD_XPM_MSG, 1);
        cub3d->torch_sprites[i] = ft_new_sprite(cub3d, sprite_paths[i]);
        i++;
    }
}

void    game_initialize(t_cub3d *cub3d)
{
    cub3d->keyboard.right = 0;
    cub3d->keyboard.left = 0;
    cub3d->keyboard.top = 0;
    cub3d->keyboard.bottom = 0;
    cub3d->keyboard.right_rotate = 0;
    cub3d->keyboard.left_rotate = 0;
    if (BONUS_FLAG)
        cub3d->mouse_set = 1;
    else
        cub3d->mouse_set = 0;
    cub3d->player.dirX = 0;
    cub3d->player.dirY = -1;
    cub3d->raycast.planeX = 0.66f;
    cub3d->raycast.planeY = 0;
    cub3d->move_speed = MOVE_SPEED;
    cub3d->camera_speed = CAMERA_SPEED;
    init_player_direction(cub3d);
    init_animation_sprites(cub3d);
}
