/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:16:14 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/29 04:51:21 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <ctype.h>
# include "../libft/include/libft.h"
# include "../mlx-linux/mlx.h"

# define M_PI 3.14159265358979323846

/*
** Game screen settings
*/

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 900

/*
** Game settings
*/

# define CAMERA_SPEED 0.01
# define MOVE_SPEED 0.025

/*
** Minimap settings
*/

# define PIXEL_PER_CUBE 10
# define CUBE_PER_LINE 20
# define SIZE_AROUND_PLAYER 10
# define MINIMAP_WIDTH (PIXEL_PER_CUBE * CUBE_PER_LINE)
# define MINIMAP_HEIGHT (PIXEL_PER_CUBE * CUBE_PER_LINE)
# define MINIMAP_CENTER (MINIMAP_WIDTH / 2)
# define DIRECTION_LINE_SIZE 10
# define DIRECTION_LINE_WIDTH 1.5
# define MINIMAP_FLOOR_COLOR 0xDE9151
# define MINIMAP_PLAYER_COLOR 0xBB0A21
# define MINIMAP_WALL_COLOR 0x6E7E85
# define MINIMAP_OUTMAP_COLOR 0x001A23

/*
** Overlay settings
*/

# define OVERLAY_HEIGHT (SCREEN_HEIGHT - SCREEN_WIDTH)
# define OVERLAY_WIDTH SCREEN_WIDTH
# define OVERLAY_BACKGROUND_COLOR 0x3F7CAC
# define LIFE_POS_X 100
# define LIFE_POS_Y (SCREEN_WIDTH + 20)
# define LIFE_COLOR 0xFFFFFF

/*
** Raycast settings
*/

# define SIDE1_COLOR 0x0000FF
# define SIDE2_COLOR 0x00FF00

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
# define CTRL 65507

/*
** Game data structures
*/

typedef struct s_tex
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}	t_tex;

typedef struct s_keyboard
{
	uint8_t	left;
	uint8_t	right;
	uint8_t	top;
	uint8_t	bottom;
}	t_keyboard;

typedef struct s_colors
{
	int			sky;
	int			floor;
}	t_colors;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	int		life;
}	t_player;

typedef struct s_raycast
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	planeX;
	double	planeY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}	t_raycast;

typedef struct s_cub3d
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			height;
	int			width;
	uint8_t		mouse_set;
    t_tex		minimap_img;
    t_tex		overlay_img;
	t_tex		raycast_img;
	t_colors	colors;
	t_keyboard	keyboard;
	t_raycast	raycast;
	t_player	player;
}	t_cub3d;

/*
** Initialization functions
*/

void    img_initialize(t_cub3d *cub3d, t_tex *minimap_img, int width, int height);
void    window_initialize(t_cub3d *cub3d);
void    game_initialize(t_cub3d *cub3d);

/*
** Game functions
*/

void    game_loop(t_cub3d *cub3d);
void    mouse_rotation(t_cub3d *cub3d);
void	set_mouse(t_cub3d *cub3d);
void    raycast(t_cub3d *cub3d, t_raycast *raycast);

/*
** Minimap and overlay functions
*/

void    put_minimap(t_cub3d *cub3d);
void    put_overlay(t_cub3d *cub3d);

/*
** Parsing functions
*/

void    parsing(t_cub3d *cub3d);

/*
** Tools functions
*/

int     get_trgb(int t, int r, int g, int b);
float  	get_distance(float x1, float y1, float x2, float y2);

/*
** Exit functions
*/

void    exit_game(t_cub3d *cub3d, char *msg, int exit_status);
int     exit_button(t_cub3d *cub3d);

#endif