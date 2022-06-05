/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:57:40 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 18:58:14 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	insert_torch(t_cub3d *cub3d)
{
	int				x;
	int				y;
	unsigned char	*pixel;

	y = 0;
	while (y < cub3d->torch_sprites[0].y)
	{
		x = 0;
		while (x < cub3d->torch_sprites[0].x)
		{
			pixel = &cub3d->torch_sprites[0].pixels[y
				* cub3d->torch_sprites[0].line_len + x
				* (cub3d->torch_sprites[0].bits_per_pixel / 8)];
			if (pixel[2] != 42 && pixel[1] != 255 && pixel[0] != 2)
				put_pixel_to_img(&cub3d->raycast_img, TORCH_POS_X + x,
					TORCH_POS_Y + y, get_trgb(0, pixel[2], pixel[1], pixel[0]));
			x++;
		}
		y++;
	}
}

void	insert_flame(t_cub3d *cub3d)
{
	int				x;
	int				y;
	static int		frame = 10;
	unsigned char	*pixel;

	y = 0;
	pixel = NULL;
	while (y < cub3d->torch_sprites[frame / 10].y)
	{
		x = 0;
		while (x < cub3d->torch_sprites[frame / 10].x)
		{
			pixel = &cub3d->torch_sprites[frame / 10]
				.pixels[y * cub3d->torch_sprites[frame / 10].line_len + x
				* (cub3d->torch_sprites[frame / 10].bits_per_pixel / 8)];
			if (pixel[2] != 0 && pixel[1] != 0 && pixel[0] != 0)
				put_pixel_to_img(&cub3d->raycast_img, FIRE_POS_X + x,
					FIRE_POS_Y + y, get_trgb(0, pixel[2], pixel[1], pixel[0]));
			x++;
		}
		y++;
	}
	frame++;
	if (frame > 70)
		frame = 10;
}
