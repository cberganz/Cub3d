/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:03:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/05/29 14:31:06 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_and_exit(int exit_code)
{
	del_garbage(MAIN);
	del_garbage(LOOP);
	exit(exit_code);
}

void	error_message_and_exit(int exit_code, char *message)
{
	printf(RED "Error\n%s\n" RESET, message);
	free_and_exit(exit_code);
}
