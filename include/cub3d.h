/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:16:14 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/01 17:27:52 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <ctype.h>
# include <stdbool.h>
# include <stdio.h>
# include "../libft/include/libft.h"
# include "../mlx-linux/mlx.h"

# define M_PI 3.14159265358979323846

/*
** print color
*/

# define RED     "\x1b[31;1m"
# define RESET   "\x1b[0m"
/*
** Game screen settings
*/

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800
# define TEXT_WIDTH 64 
# define TEXT_HEIGHT 64
/*
** Game settings
*/

# define CAMERA_SPEED 0.01
# define MOVE_SPEED 0.025
# define ROTATION_ANGLE 1.5
# define HITBOX_SIZE 0.2

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
** Garbage Collector
*/
# define MAIN 0
# define LOOP 1

/*
** Error Messages
*/
#define FD_CUB_MSG "You should pass an existing file with '.cub' extension"
#define FD_XPM_MSG "You should pass an existing texture file with '.xpm' extension"
#define COLOR_FORMAT_ERROR "Invalid color format"
#define TEXTURES_INSTRUCTION_ERROR "Invalid textures instructions"
#define INCORECT_MAP_MSG "Map is incorrect"
#define MALLOC_ERR_MSG "Malloc error"
#define FD_ARG_ERR_MSG "Failed opening argument file"

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
	uint8_t	right_rotate;
	uint8_t	left_rotate;
}	t_keyboard;

typedef struct s_colors
{
	int			sky;
	int			floor;
}	t_colors;

typedef struct s_player
{
	char	start_dir;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
}	t_player;

typedef struct s_image {
	void			*reference;
	int				x;
	int				y;
	unsigned char	*pixels;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}				t_image;

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
	int 	texNum;
	int 	texX;
	double 	wallX;
}	t_raycast;

// AJOUTE PAR ROBIN 
typedef struct	s_color
{
	int	octet[3];
}				t_color;


typedef struct	s_wall_textures
{
	char		cardinals_array[6][4];
	char		*textures_paths[6];
	t_color		colors[2];
}				t_wall_textures;

typedef struct	s_map
{
	unsigned int		width;
	unsigned int		height;
	char				**map_strs;
}				t_map;


// AJOUTE PAR ROBIN 

typedef struct s_cub3d
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			height;
	int			width;
	// AJOUTE PAR ROBIN 
	
	char			**file_to_strs;
	t_wall_textures wall_textures;
	t_image			sprites[4];
	t_map			map_struct;
	
	// AJOUTE PAR ROBIN 
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
**	PARSING ROBIN
*/
void	split_file_string(t_cub3d *prog, char *file_name);
bool	parse_wall_textures(t_cub3d *prog);
bool	is_space_line(char *str);
void	parse_map(t_cub3d *prog);
void	global_parsing(t_cub3d *prog, char *file_name);
void	find_player_data(t_map *map, t_player *player);
void	init_sprites(t_cub3d *prgm);

/*
**	CHECK ERRORS ROBIN
*/
bool	textures_paths_are_correct(t_cub3d prog);
bool	is_valid_extension_path(char *path, char *extension);
bool	file_exist(char *path);
bool	are_all_instructions_present(t_wall_textures textures);
bool	are_color_instruction_valid(t_wall_textures *textures);
bool	is_valid_map(t_map map);

/*
**	UTILS ROBIN
*/
void	free_and_exit(int exit_code);
bool	is_int_overflow(char *str_nbr);
bool	is_str_digit(char *str);
void	error_message_and_exit(int exit_code, char *message);

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