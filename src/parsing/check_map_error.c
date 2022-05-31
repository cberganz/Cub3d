/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:44:44 by rbicanic          #+#    #+#             */
/*   Updated: 2022/05/29 20:05:45 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	extrem_lines_are_correct(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (false);
		line++;
	}
	return (true);
}

bool	ground_is_surronded_by_walls(t_map map)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 1;
	while (map.map_strs[y] && y < map.height - 1)
	{
		while (map.map_strs[y][x])
		{
			if ((x == 0 && map.map_strs[y][x] == '0')
				|| is_space_line(map.map_strs[y]))
				return (false);
			if ((map.map_strs[y][x] == '0' || map.map_strs[y][x] == 'N')// erreur ici pas que N
				&& (map.map_strs[y][x + 1] == ' ' 
				|| map.map_strs[y][x - 1] == ' '
				|| map.map_strs[y + 1][x] == ' '
				|| map.map_strs[y - 1][x] == ' '))
				return (false);
			x++;
		}
		x = 0;
		y++;
	}
	return (true);
}

bool	map_charset_is_correct(t_map map)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	player_charset_nbr;

	player_charset_nbr = 0;
	x = 0;
	y = 0;
	while (map.map_strs[y])
	{
		while (map.map_strs[y][x])
		{
			if (map.map_strs[y][x] == 'N' || map.map_strs[y][x] == 'S'
				|| map.map_strs[y][x] == 'E' || map.map_strs[y][x] == 'W')
				player_charset_nbr++;
			else if (map.map_strs[y][x] != '0' && map.map_strs[y][x] != '1'
				&& map.map_strs[y][x] != ' ')
				return (false);
			x++;
		}
		x = 0;
		y++;
	}
	return (player_charset_nbr == 1);
}

bool	is_valid_map(t_map map)
{
	if (map.width < 3 || map.height < 3)
		return (false);
	if (!extrem_lines_are_correct(map.map_strs[0])
		|| !extrem_lines_are_correct(map.map_strs[map.height - 1]))
		return (false);
	if (!ground_is_surronded_by_walls(map) || !map_charset_is_correct(map))
		return (false);
	return (true);
}

void	find_player_data(t_map *map, t_player *player)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 1;
	while (map->map_strs[y] && y < map->height - 2)
	{
		while (map->map_strs[y][x])
		{
			if (map->map_strs[y][x] == 'N' || map->map_strs[y][x] == 'S'
				|| map->map_strs[y][x] == 'E' || map->map_strs[y][x] == 'W')
			{
				player->start_dir = map->map_strs[y][x];
				map->map_strs[y][x] = '0';
				player->posX = x;
				player->posY = y;
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
