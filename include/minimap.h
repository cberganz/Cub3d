/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:06:04 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/27 02:55:56 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "../libft/include/libft.h"
# include "../mlx-linux/mlx.h"

/*
** Keyboard keys
*/

# define D 100
# define A 97
# define W 119
# define S 115
# define RIGHT 65363
# define LEFT 65361
# define TOP 65362
# define BOTTOM 65364
# define ESC 65307

# define WIDTH 800
# define HEIGHT 800
# define PIXEL_PER_CUBE 8
# define CUBE_PER_LINE 21
# define SIZE_AROUND_PLAYER 10
# define CENTER_XY 10
# define MINIMAP_WIDTH (PIXEL_PER_CUBE * CUBE_PER_LINE)
# define MINIMAP_HEIGHT (PIXEL_PER_CUBE * CUBE_PER_LINE)

typedef struct s_tex
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}	t_tex;

typedef struct s_minimap
{
	char	**map;
	int		height;
	int		width;
	void	*mlx;
	void	*mlx_win;
	int		p_pos_x;
	int		p_pos_y;
    t_tex	map_img;
}	t_minimap;

#endif