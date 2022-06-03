/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:24:50 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/03 16:01:20 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_space_line(char *str)
{
	int		i;
	bool	all_line_char_are_spaces;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	all_line_char_are_spaces = (str[i] == '\0');
	return (all_line_char_are_spaces);	
}

unsigned int	get_map_length(char	**file_map_part, t_map map)
{
	unsigned int i;
	unsigned int max_len;

	i = 0;
	max_len = 0;
	while (file_map_part[i] && i < map.height)
	{
		if (ft_strlen(file_map_part[i]) > max_len)
			max_len = ft_strlen(file_map_part[i]);
		i++;
	}
	return (max_len);
}

unsigned int	get_map_height(char **file_map_part)
{
	unsigned int i;

	i = 0;
	while (file_map_part[i])
		i++;
	i--;
	while (i >= 0 && is_space_line(file_map_part[i]))
		i--;
	return (i + 1);
}

void	map_to_strs(t_map *map, char **file_map_part)
{
	unsigned int	i;

	i = 0;
	map->map_strs = mem_alloc((map->height + 1) * sizeof(char *),  NULL, MAIN);
	if (!map->map_strs)
		error_message_and_exit(1, MALLOC_ERR_MSG);
	while (file_map_part[i] && i < map->height)
	{
		if (mem_alloc((map->width + 1) * sizeof(char), (void**)&map->map_strs[i], MAIN))
			error_message_and_exit(1, MALLOC_ERR_MSG);
		ft_memset(map->map_strs[i], ' ', map->width);
		ft_memcpy(map->map_strs[i], file_map_part[i], ft_strlen(file_map_part[i]));
		map->map_strs[i][map->width] = '\0';
		i++;
	}
	map->map_strs[i] = NULL;
}

void	parse_map(t_cub3d *prog)
{
	int	i;

	i = 0;
	while (prog->file_to_strs[i] && i < 6)
		i++;
	if (i != 6 || !prog->file_to_strs[i])
		error_message_and_exit(1, INCORECT_MAP_MSG);
	while (is_space_line(prog->file_to_strs[i]))
		i++;
	prog->map_struct.height = get_map_height(&prog->file_to_strs[i]);
	prog->map_struct.width = get_map_length(&prog->file_to_strs[i], prog->map_struct);
	map_to_strs(&prog->map_struct, &prog->file_to_strs[i]);
}

void	init_doors(t_cub3d *cub3d, t_map map)
{
	unsigned int	x;
	unsigned int	y;
	int				i;

	y = 0;
	i = 0;
	while (map.map_strs[y])
	{
		x = 0;
		while (map.map_strs[y][x])
		{
			if (map.map_strs[y][x] == 'D')
			{
				cub3d->doors[i].x = x;
				cub3d->doors[i].y = y;
				cub3d->doors[i].step_percent = 0;
				cub3d->doors[i].increment_step = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	alloc_doors(t_cub3d *cub3d, t_map map)
{
	unsigned int	x;
	unsigned int	y;

	cub3d->doors_nbr = 0;
	y = 0;
	while (map.map_strs[y])
	{
		x = 0;
		while (map.map_strs[y][x])
		{
			if (map.map_strs[y][x] == 'D')
				cub3d->doors_nbr++;
			x++;
		}
		y++;
	}
	if (mem_alloc(cub3d->doors_nbr * sizeof(t_door), (void**)&cub3d->doors, MAIN))
		exit_game(cub3d, MALLOC_ERR_MSG, 1);
}
