/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:29 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/10 17:40:35 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	init_data(t_data *data, int argc, char **argv)
{
	if (argc == 2)
	{
		data->set.sp = NULL;
		data->set.pl = NULL;
		data->set.cy = NULL;
		data->width = 1600;
		data->height = 900;
		data->aspect_ratio = (float)data->width / (float)data->height;
		open_file(argv[1], data);
	}
	else
		error("Wrong nbr of Arguments", data);
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(data->width, data->height, "miniRT", true);
	data->img = mlx_new_image(data->window, data->width, data->height);
}
