/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:56:01 by rbicanic          #+#    #+#             */
/*   Updated: 2022/05/29 19:45:13 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define SKY_COLOR prog->wall_textures.colors[1]
#define FLOOR_COLOR prog->wall_textures.colors[0]

void	init_structure(t_cub3d *prog)
{
	prog->file_to_strs = NULL;
	prog->wall_textures = (t_wall_textures)
	{
		.cardinals_array = {"NO ", "SO ", "WE ", "EA ", "F ", "C "},
		.textures_paths = {NULL, NULL, NULL, NULL, NULL, NULL}
	};
	prog->map_struct.map_strs = NULL;
	prog->map_struct.height = 0;
	prog->map_struct.width = 0;

}

void	global_parsing(t_cub3d *prog, char *file_name)
{
	if (!is_valid_extension_path(file_name, ".cub") || !file_exist(file_name))
		error_message_and_exit(1, FD_CUB_MSG);
	init_structure(prog);
	split_file_string(prog, file_name);
	parse_wall_textures(prog);
	if (!are_all_instructions_present(prog->wall_textures)
		|| !textures_paths_are_correct(*prog))
		error_message_and_exit(1, FD_XPM_MSG);
	if (!are_color_instruction_valid(&prog->wall_textures))
		error_message_and_exit(1, COLOR_FORMAT_ERROR);
	parse_map(prog);
	if (!is_valid_map(prog->map_struct))
		error_message_and_exit(1, INCORECT_MAP_MSG);
	find_player_data(&prog->map_struct, &prog->player);
	prog->colors.sky = get_trgb(0, SKY_COLOR.octet[0], SKY_COLOR.octet[1], SKY_COLOR.octet[2]);//utiliser couleurs du fichier
    prog->colors.floor = get_trgb(0, FLOOR_COLOR.octet[0], FLOOR_COLOR.octet[1], FLOOR_COLOR.octet[2]);//utiliser couleurs du fichier
	del_garbage(LOOP);
}
