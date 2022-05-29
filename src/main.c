/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:18:21 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/29 03:11:26 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv, char **envp)
{
    t_cub3d   cub3d;

    (void)argc;
    (void)argv;
    if (!envp)
        return (0);
    window_initialize(&cub3d);
    parsing(&cub3d);
    img_initialize(&cub3d, &cub3d.minimap_img, MINIMAP_WIDTH, MINIMAP_HEIGHT);
    img_initialize(&cub3d, &cub3d.overlay_img, OVERLAY_WIDTH, OVERLAY_HEIGHT);
    img_initialize(&cub3d, &cub3d.raycast_img, SCREEN_WIDTH, SCREEN_WIDTH);
    game_initialize(&cub3d);
    game_loop(&cub3d);
    return (0);
}
